/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:10:26 by achajar           #+#    #+#             */
/*   Updated: 2025/04/17 17:10:35 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minitalk.h"

static volatile sig_atomic_t	g_signal_acknowledged = 0;

static void	client_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		g_signal_acknowledged = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr("server confirmed message received successfully.\n");
		exit(0);
	}
}

static void	send_char_as_signals(char c, int server_pid)
{
	int				bit_index;
	unsigned char	current_char;

	current_char = c;
	bit_index = 8;
	while (bit_index--)
	{
		g_signal_acknowledged = 0;
		if (current_char >> bit_index & 1)
		{
			if (kill(server_pid, SIGUSR1) < 0)
				print_error();
		}
		else if (kill(server_pid, SIGUSR2) < 0)
			print_error();
		while (!g_signal_acknowledged)
			pause();
	}
	usleep(90);
}

static void	send_string(char *message, int server_pid)
{
	int	i;

	i = 0;
	while (message[i])
		send_char_as_signals(message[i++], server_pid);
	send_char_as_signals('\0', server_pid);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa_client;

	if (argc != 3)
	{
		ft_putstr("\033[1;31mUsage: ./client <Server_PID> <Message>\033[0m\n");
		return (1);
	}
	sa_client.sa_sigaction = &client_signal_handler;
	sa_client.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa_client.sa_mask);
	sigaction(SIGUSR1, &sa_client, 0);
	sigaction(SIGUSR2, &sa_client, 0);
	server_pid = ft_atoi(argv[1]);
	if (ft_atoi(argv[1]) <= 0 || is_pid_valid(argv[1]))
		print_error();
	send_string(argv[2], server_pid);
	return (0);
}

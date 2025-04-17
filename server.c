/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achajar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:10:40 by achajar           #+#    #+#             */
/*   Updated: 2025/04/17 17:10:42 by achajar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_byte_received(int *bit_count_ptr, char *byte_ptr,
		int sender_pid)
{
	if (*byte_ptr == '\0')
		kill(sender_pid, SIGUSR2);
	ft_putstr(byte_ptr);
	*byte_ptr = 0;
	*bit_count_ptr = 0;
}

static void	server_signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	received_bit_count;
	static char	current_byte;
	static int	current_sender_pid;
	static int	last_sender_pid;

	if (!last_sender_pid)
		last_sender_pid = info->si_pid;
	current_sender_pid = info->si_pid;
	if (last_sender_pid != current_sender_pid)
	{
		received_bit_count = 0;
		current_byte = 0;
		last_sender_pid = current_sender_pid;
	}
	(void)context;
	current_byte <<= 1;
	if (sig == SIGUSR1)
		current_byte += 1;
	received_bit_count++;
	if (received_bit_count == 8)
		handle_byte_received(&received_bit_count, &current_byte,
			current_sender_pid);
	usleep(90);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa_server;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa_server.sa_sigaction = &server_signal_handler;
	sa_server.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa_server.sa_mask);
	sigaction(SIGUSR1, &sa_server, 0);
	sigaction(SIGUSR2, &sa_server, 0);
	while (1)
		pause();
	return (0);
}

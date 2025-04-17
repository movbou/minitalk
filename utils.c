
#include "minitalk.h"

void	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void	ft_putnbr(int n)
{
	long	num_long;
	size_t	i;
	char	buffer[11];

	num_long = n;
	if (num_long == 0)
		write(1, "0", 1);
	if (num_long < 0)
	{
		num_long = -num_long;
		write(1, "-", 1);
	}
	i = 0;
	while (num_long)
	{
		buffer[i] = num_long % 10 + 48;
		num_long /= 10;
		i++;
	}
	while (i > 0)
		write(1, &buffer[--i], 1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		result = result * 10 + str[i++] - 48;
	return (result * sign);
}

int	is_pid_valid(const char *pid_str)
{
	int	i;

	i = 0;
	while (pid_str[i])
	{
		if (pid_str[i] < '0' || pid_str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	print_error(void)
{
	ft_putstr("\033[1;31mWrong PID ❌\033[0m\n");
	exit(1);
}

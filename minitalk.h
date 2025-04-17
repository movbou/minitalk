
#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

void	ft_putnbr(int n);
void	ft_putstr(char *str);
int		ft_atoi(const char *str);

int		is_pid_valid(const char *pid_str);
void	print_error(void);

#endif

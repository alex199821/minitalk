/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:12:30 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/20 03:51:31 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

char	bits_to_char(const char *bits)
{
	char	result;
	int		i;

	result = 0;
	i = 0;
	while (i < 8)
	{
		result = (result << 1) | (bits[i] - '0');
		i++;
	}
	return (result);
}

void	handler(int signum, siginfo_t *info, void *more_info)
{
	static char		bit_str[8];
	static char		c = 0;
	static int		bit = 0;
	static pid_t	client = 0;

	if (info->si_pid)
		client = info->si_pid;
	if (SIGUSR1 == signum)
	{
		// printf("SIGUSR1: %d\n", 0);
		bit_str[bit] = 0;
		// c |= (0b10000000 >> bit);
	}
	else if (SIGUSR2 == signum)
	{
		// printf("SIGUSR2: %d\n", 1);
		bit_str[bit] = 1;
		// c &= ~(0x80 >> bit);
	}
	bit++;
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(STDOUT_FILENO, "\n", 1);
			Kill(client, SIGUSR2);
			c = 0;
			return ;
		}
		// write(STDOUT_FILENO, &c, 1);
		bits_to_char(bit_str);
		c = 0;
	}
	kill(client, SIGUSR1);
}

int	main(int ac, char **av)
{
	if (ac != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}
	printf("Server PID: %d\n", getpid());
	Signal(SIGUSR1, handler, true);
	Signal(SIGUSR2, handler, true);
	while (1500)
		pause();
	return (EXIT_SUCCESS);
}

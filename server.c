/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:12:30 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/20 22:41:43 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

// cc -o server server.c utils.c

char	bits_to_char(char *bits)
{
	char	result;
	int		i;

	result = 0;
	i = 0;
	while (bits[i])
	{
		result = (result << 1) | (bits[i] - '0');
		i++;
	}
	return (result);
}

void	handler(int signum, siginfo_t *info, void *more_info)
{
	static char		bit_str[9];
	static int		bit = 0;
	static pid_t	client = 0;
	char			c;

	if (info->si_pid)
		client = info->si_pid;
	if (SIGUSR1 == signum)
		bit_str[bit] = '1';
	else if (SIGUSR2 == signum)
		bit_str[bit] = '0';
	bit++;
	if (CHAR_BIT == bit)
	{
		bit = 0;
		if (bits_to_char(bit_str) == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			send_singal(client, SIGUSR2);
			return ;
		}
		c = bits_to_char(bit_str);
		write(1, &c, 1);
	}
	send_singal(client, SIGUSR1);
}

int	main(int ac, char **av)
{
	if (ac != 1)
	{
		write(1, "Incorrect Number of Arguments\n", 30);
		return (EXIT_FAILURE);
	}
	printf("Server PID: %d\n", getpid());
	singal_handle(SIGUSR1, handler, true);
	singal_handle(SIGUSR2, handler, true);
	while (1342)
		pause();
	return (EXIT_SUCCESS);
}

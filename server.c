/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:12:30 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/22 00:44:04 by macbook          ###   ########.fr       */
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
	static char	bit_str[9];
	static int	bit = 0;
	static int	client_pid = 0;
	char		c;

	(void)more_info; 
	if (info->si_pid) client_pid = info->si_pid;
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
			send_singal(client_pid, SIGUSR2);
			return ;
		}
		c = bits_to_char(bit_str);
		write(1, &c, 1);
	}
	send_singal(client_pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
	{
		write(1, "Incorrect Number of Arguments\n", 30);
		return (EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", getpid());
	singal_configure(SIGUSR1, handler);
	singal_configure(SIGUSR2, handler);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

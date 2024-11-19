/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:12:30 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/19 21:13:51 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// void	handler(int signum, siginfo_t *info, void *more_info)
// {
// 	static char		c = 0;
// 	static int		bit = 0;
// 	static pid_t	client = 0;

// 	if (info->si_pid) 
// 		client = info->si_pid;
// 	if (SIGUSR1 == signum)
// 		c |= (0b10000000 >> bit);
// 	else if (SIGUSR2 == signum)
// 		c &= ~(0x80 >> bit);
// 	bit++
// 	;
// 	if (CHAR_BIT == bit)
// 	{
// 		bit = 0;
// 		if ('\0' == c)
// 		{
// 			write(STDOUT_FILENO, "\n", 1);
// 			Kill(client, SIGUSR2);
// 			c = 0;
// 			return ;
// 		}
// 		write(STDOUT_FILENO, &c, 1);
// 		c = 0;
// 	}
// 	kill(client, SIGUSR1);
// }

// int	main(int ac, char **av)
// {
// 	if (ac != 1)
// 	{
// 		fputs("Usage: ./server\n", stderr);
// 		return (EXIT_FAILURE);
// 	}
	
// 	printf("Server PID: %d\n", getpid());

// 	Signal(SIGUSR1, handler, true);
// 	Signal(SIGUSR2, handler, true);
// 	while (1345)
// 		pause();
// 	return (EXIT_SUCCESS);
// }

static void	handler(int sig, siginfo_t *info, void *more_info)
{
	static char		c = 0;
	static int		bit = 0;
	static pid_t	goku = 0;


	if (info->si_pid) 
		goku = info->si_pid;

	if (SIGUSR1 == sig)
		c |= (0b10000000 >> bit);
	else if (SIGUSR2 == sig)
		c &= ~(0x80 >> bit);
	bit++;

	if (CHAR_BIT == bit)
	{
		bit = 0;
		if ('\0' == c)
		{
			write(STDOUT_FILENO, "\n", 1);
			Kill(goku, SIGUSR2);
			c = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	Kill(goku, SIGUSR1);
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

	while (1337)
		pause();
		
	return (EXIT_SUCCESS);
}
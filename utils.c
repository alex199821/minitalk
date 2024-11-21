/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:08 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/21 01:00:10 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	singal_configure(int signo, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = handler;
	// sigemptyset(&sa.sa_mask);
	// sigaddset(&sa.sa_mask, SIGUSR1);
	// sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
	{
		perror("Sigaction Failed");
		exit(EXIT_FAILURE);
	}
}

void	send_singal(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
	{
		perror("Kill Failed");
		exit(EXIT_FAILURE);
	}
}

int	is_ready(int ready)
{
	static int	i = 0;

	if (ready == 0)
		i = 0;
	else if (ready == 1)
		i = 1;
	return (i);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
	{
		i++;
	}
	return (i);
}

// void	singal_handle(int signo, void *handler, bool use_siginfo)
// {
// 	struct sigaction	sa;

// 	// if (use_siginfo)
// 	// {
// 	// 	sa.sa_flags = SA_SIGINFO;
// 	// 	sa.sa_sigaction = handler;
// 	// }
// 	// else
// 	// {
// 	// 	sa.sa_handler = handler;
// 	// }
// 	sa.sa_flags = SA_SIGINFO;
// 	// sa.sa_sigaction = handler;
// 	sa.sa_handler = handler;
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGUSR1);
// 	sigaddset(&sa.sa_mask, SIGUSR2);
// 	printf("- sa_flags: %d\n", sa.sa_flags);
// 	if (sigaction(signo, &sa, NULL) < 0)
// 	{
// 		perror("Sigaction Failed");
// 		exit(EXIT_FAILURE);
// 	}
// }
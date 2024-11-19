/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:19:55 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/19 21:15:07 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// volatile sig_atomic_t g_server = BUSY;

// void rec_handler(int signo)
// {
// 	g_server = READY;
// }

// void end_handler(int signo)
// {
// 	write(STDOUT_FILENO, "Ok!", 3);
// }

// void	send_char(char c, pid_t server)
// {
// 	int bit = 0;
// 	while (bit < CHAR_BIT)
// 	{
// 		if (c & (0x80 >> bit))
// 			Kill(server, SIGUSR1);
// 		else
// 			Kill(server, SIGUSR2);
// 		++bit;
// 	}
// 	while(BUSY == g_server)
// 		usleep(42);

// 	g_server = BUSY;
// }

// int	main(int argc, char *argv[])
// {
// 	pid_t server;
// 	char *message;
// 	int i;

// 	i = 0;
// 	if (argc != 3)
// 	{
// 		write(1, "Error\n", 6);
// 		exit(EXIT_FAILURE);
// 	}

// 	server = atoi(argv[1]);
// 	message = argv[2];

// 	Signal(SIGUSR1, rec_handler, false);
// 	Signal(SIGUSR1, end_handler, false);

// 	while (message[i])
// 	{
// 		send_char(message[i], server);
// 		i++;
// 	}
// 	send_char('\0', server);

// 	return (EXIT_SUCCESS);
// }


volatile sig_atomic_t	g_kingKai = BUSY;

static void	end_handler(int sig)
{
	fputs("\n\t✅ Message received ✅\n", stdout);
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int sig)
{
	g_kingKai = READY;
}

static void	send_char(char c, pid_t kingKai)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{

		if (c & (0x80 >> bit))
			Kill(kingKai, SIGUSR1);
		else
			Kill(kingKai, SIGUSR2);
		bit++;

		while (BUSY == g_kingKai)
			usleep(42);

		g_kingKai = BUSY;
	}
}

int	main(int ac, char **av)
{
	pid_t	kingKai;
	char	*message;
	int		i;

	if (ac != 3)
	{
		fputs("Usage: ./client <kingKai> \"message\"\n", stderr);
		return (EXIT_FAILURE);
	}
	kingKai = atoi(av[1]);
	message = av[2];

	Signal(SIGUSR1, ack_handler, false);
	Signal(SIGUSR2, end_handler, false);

	i = 0;
	while (message[i])
		send_char(message[i++], kingKai);
	send_char('\0', kingKai);

	return (EXIT_SUCCESS);
}
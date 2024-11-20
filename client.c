/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:19:55 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/20 20:13:37 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

// cc -o client client.c utils.c

volatile sig_atomic_t	g_server = BUSY;

int is_busy(int busy)
{
	static int i;
	if(busy == 0) 
		i = 0;
	else if(busy == 1)
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

void	rec_handler(int signo)
{
	g_server = READY;
}

void	end_handler(int signo)
{
	write(STDOUT_FILENO, "Ok!", 3);
	exit(EXIT_SUCCESS);
}

char	*char_to_bits(unsigned char c)
{
	int				i;
	int				j;
	unsigned char	bit;
	char			*bits_ar;

	i = 0;
	j = 8;
	bits_ar = (char *)malloc((j + 1) * sizeof(char));
	if (!bits_ar)
		return (NULL);
	while (i < 8)
	{
		j--;
		bit = (c >> j & 1) + '0';
		bits_ar[i] = bit;
		i++;
	}
	bits_ar[i] = '\0';
	return (bits_ar);
}

void	send_char(char c, pid_t server)
{
	int		i;
	char	mask;
	char	*bits_array;

	bits_array = char_to_bits(c);
	if (!bits_array)
		return ;
	i = 0;
	while (bits_array[i])
	{
		printf("%c", bits_array[i]);
		if (bits_array[i] == '1')
			Kill(server, SIGUSR1);
		else if (bits_array[i] == '0')
			Kill(server, SIGUSR2);
		i++;
		while (BUSY == g_server)
			usleep(42);
		g_server = BUSY;
	}
	free(bits_array);
}

int	main(int argc, char *argv[])
{
	pid_t	server;
	char	*message;
	int		i;

	if (argc != 3)
	{
		write(1, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	server = atoi(argv[1]);
	message = argv[2];
	Signal(SIGUSR1, rec_handler, false);
	Signal(SIGUSR2, end_handler, false);
	i = 0;
	while (message[i])
	{
		send_char(message[i], server);
		i++;
	}
	send_char('\0', server);
	return (EXIT_SUCCESS);
}

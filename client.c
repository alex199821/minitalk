/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:19:55 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/21 01:02:22 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	rec_handler(void)
{
	is_ready(1);
}

void	end_handler(void)
{
	write(STDOUT_FILENO, "Message Recieved\n", 17);
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
	char	*bits_array;

	bits_array = char_to_bits(c);
	if (!bits_array)
		return ;
	i = 0;
	while (bits_array[i])
	{
		if (bits_array[i] == '1')
			send_singal(server, SIGUSR1);
		else if (bits_array[i] == '0')
			send_singal(server, SIGUSR2);
		i++;
		while (!is_ready(-1))
			usleep(42);
		is_ready(0);
	}
	free(bits_array);
}

// void	leaks(void)
// {
// 	system("leaks client");
// }
// atexit(leaks);

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
	singal_configure(SIGUSR1, rec_handler, false);
	singal_configure(SIGUSR2, end_handler, false);
	i = 0;
	while (message[i])
	{
		send_char(message[i], server);
		i++;
	}
	send_char('\0', server);
	return (EXIT_SUCCESS);
}

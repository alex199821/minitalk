/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:07 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/17 01:14:57 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd(char c, int fd, int *count)
{
	int	written;

	if (*count == -1)
		return ;
	written = write(fd, &c, 1);
	if (written == -1)
	{
		*count = -1;
		return ;
	}
	else
		*count += written;
}

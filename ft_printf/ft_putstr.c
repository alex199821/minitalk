/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:30:41 by auplisas          #+#    #+#             */
/*   Updated: 2024/10/17 01:42:07 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd, int *count)
{
	int	i;
	int	str_len;

	if (!s)
		ft_putstr_fd("(null)", 1, count);
	else
	{
		str_len = ft_strlen(s);
		i = 0;
		while (i < str_len)
		{
			ft_putchar_fd(s[i], fd, count);
			i++;
		}
	}
}

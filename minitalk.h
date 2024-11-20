/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:18:35 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/20 22:20:28 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUSY 0
# define READY 1
// server.c
void	singal_handle(int signo, void *handler, bool use_siginfo);
void	send_singal(pid_t pid, int signo);
int		is_ready(int ready);
size_t	ft_strlen(const char *c);
#endif

// #ifndef MINITALK_H
// # define MINITALK_H

// # include <stdio.h>
// # include <errno.h>
// # include <string.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <signal.h>
// # include <limits.h>
// # include <stdbool.h>

// #define BUSY	0
// #define READY	1

// void	Signal(int sig, void *handler, bool use_siginfo);
// void	Kill(pid_t pid, int signum);

// #endif
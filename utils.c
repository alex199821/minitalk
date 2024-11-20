/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:47:08 by auplisas          #+#    #+#             */
/*   Updated: 2024/11/20 00:23:33 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	Signal(int signo, void *handler, bool use_siginfo)
{
    struct sigaction	sa = {0};
    
	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
	{
		sa.sa_handler = handler;
	}
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
	{
		perror("Sigaction Failed");
		exit(EXIT_FAILURE);
	}
}

void	Kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
	{
		perror("Kill Failed");
		exit(EXIT_FAILURE);
	}
}

// void	Signal(int sig, void *handler, bool use_siginfo)
// {
// 	struct sigaction	sa = {0};

// 	if (use_siginfo)
// 	{
// 		sa.sa_sigaction = handler;
// 		sa.sa_flags = SA_SIGINFO;
// 	}
// 	else
// 		sa.sa_handler = handler;
 
// 	/* Block both signals during handler execution */
// 	sigemptyset(&sa.sa_mask);
// 	sigaddset(&sa.sa_mask, SIGUSR1);
// 	sigaddset(&sa.sa_mask, SIGUSR2);
    
// 	if (sigaction(sig, &sa, NULL) < 0)
// 	{
// 		perror("Signal handler setup failed");
// 		exit(EXIT_FAILURE);
// 	}
// }

// /**
//  * Kill - Wrapper for kill system call with error handling
//  * @pid: Process ID to send signal to
//  * @signum: Signal number to send
//  */
// void	Kill(pid_t pid, int signum)
// {
// 	if (kill(pid, signum) < 0)
// 	{
// 		perror("Signal transmission failed");
// 		exit(EXIT_FAILURE);
// 	}
// }


// void print_pending_signals()
// {
//     sigset_t pending;
//     if (sigpending(&pending) == -1) {
//         perror("sigpending");
//         exit(EXIT_FAILURE);
//     }

//     printf("\n=== Pending Signals ===\n");
//     for (int i = 1; i < NSIG; i++) {
//         if (sigismember(&pending, i)) {
//             printf("Signal %d (%s) is pending\n", i, strsignal(i));
//         }
//     }
//     printf("=======================\n\n");
// }

// // Function to print the list of blocked signals
// void print_blocked_signals()
// {
//     sigset_t blocked;
//     if (sigprocmask(SIG_BLOCK, NULL, &blocked) == -1) {
//         perror("sigprocmask");
//         exit(EXIT_FAILURE);
//     }

//     printf("\n=== Blocked Signals ===\n");
//     for (int i = 1; i < NSIG; i++) {
//         if (sigismember(&blocked, i)) {
//             printf("Signal %d (%s) is blocked\n", i, strsignal(i));
//         }
//     }
//     printf("=======================\n");
// }
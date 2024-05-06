/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:57:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/04 14:27:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

sig_atomic_t	*sigint_recv(void)
{
	static sig_atomic_t	sigint_recv = 0;

	return (&sigint_recv);
}

void	segfault(int signal)
{
	(void)signal;
	ft_putstr_fd("Internal Error occured\nExiting!\n", 2);
	*get_run() = 0;
	exit(1);
}

// TODO: i think we peint one nl too much when pressing control + c
void	signal_handler(int signum)
{
	if (signum == SIGTERM)
	{
		*get_run() = 0;
		return ;
	}
	else if (signum == SIGINT)
	{
		*sigint_recv() = 1;
		rl_redisplay();
		printf("\n");
	}
	else if (signum == SIGQUIT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// TODO: implement all those functions down here

// XXX: This function is being called when goign to a child process
void	signal_ignore_parent(void)
{
	// signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

// XXX: This function is being called when going back to the parent process
void	signal_restore_parent(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGSEGV, segfault);
}

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

void	signal_handler(int signum)
{
	if (signum == SIGTERM)
	{
		*g_run = false;
		return ;
	}
	if (signum == SIGINT) // TODO: handle sigint correctly to end curr task
	{
		printf("\n");
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

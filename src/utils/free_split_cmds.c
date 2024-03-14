/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:05:13 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/13 14:10:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free (split);
	return (0);
}

void	free_cmds_helper(t_variable *cmds)
{
	t_variable	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->name);
		free(cmds->value);
		free(cmds);
		cmds = tmp;
	}
	cmds = NULL;
}

void	free_cmds(t_command *cmds)
{
	t_command	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->command);
		free(cmds->args);
		free(cmds->operator_type);
		free(cmds);
		cmds = tmp;
	}
	cmds = NULL;
}

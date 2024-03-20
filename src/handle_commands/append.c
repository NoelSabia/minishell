/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:29:24 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/20 11:17:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_append(t_shell *shell, t_shunting_node *cmd1, t_shunting_node *cmd2)
{
	int	status;
	int	fd;

	status = CMD_SUCCESS;
	if (!cmd1 || !cmd2 || !shell)
		return (CMD_FAILURE);
	fd = open(cmd2->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open file");
		return (CMD_FAILURE);
	}
	if (write(fd, cmd1->value, ft_strlen(cmd1->value)) < 0)
	{
		perror("Failed to write to file");
		close(fd);
		return (CMD_FAILURE);
	}
	close(fd);
	return (status);
}

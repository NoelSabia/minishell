/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsabia <nsabia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/04/09 11:50:05 by nsabia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_chain(t_shunting_node **chain);

int	get_chain_len(t_shunting_node **chain)
{
	int				pipe_amount;

	pipe_amount = 0;
	while (chain[pipe_amount])
		pipe_amount++;
	return (pipe_amount);
}

void	child_proc(int counter, int pipe_amount, int fd[pipe_amount][2],
	pid_t pid[pipe_amount], t_shell *shell, t_shunting_node **chain)
{
	if (counter != 0)
	{
		close(fd[counter - 1][1]);
		dup2(fd[counter - 1][0], STDIN_FILENO);
	}
	if (counter != pipe_amount)
	{
		close(fd[counter][0]);
		dup2(fd[counter][1], STDOUT_FILENO);
	}
	exit(run_command(shell, chain[counter]));
}

int	parent_proc(int counter, int pipe_amount, int fd[pipe_amount][2],
	pid_t pid[pipe_amount], char *line, char buffer[4096], ssize_t bytesRead,
	int m)
{
	close(fd[counter][1]);
	if (counter != 0)
		close(fd[counter - 1][0]);
	if (counter == pipe_amount - 1)
	{
		m = 0;
		while (m <= pipe_amount)
			waitpid(pid[m++], 0, 0);
		line = malloc(1);
		line[0] = '\0';
		bytesRead = read(fd[counter][0], buffer, sizeof(buffer) - 1);
		while (bytesRead > 0)
		{
			buffer[bytesRead] = '\0';
			line = realloc(line, strlen(line) + bytesRead + 1);
			strcat(line, buffer);
			bytesRead = read(fd[counter][0], buffer,
					sizeof(buffer) - 1);
		}
		close(fd[counter][0]);
		return (1);
	}
	return (0);
}

char	*run_pipe(t_shell *shell, t_shunting_node **chain)
{
	int				pipe_amount;
	int				fd[pipe_amount][2];
	int				counter;
	pid_t			pid[pipe_amount];
	int				exit_code;
	char			*line;
	char			buffer[4096];
	ssize_t			bytesRead;
	int				m;

	counter = -1;
	line = NULL;
	ft_memset(pid, 0, sizeof(pid));
	pipe_amount = get_chain_len(chain);
	while (chain[++counter] && counter <= pipe_amount)
	{
		if (pipe(fd[counter]) == -1)
			return (NULL);
		pid[counter] = fork();
		if (pid[counter] == -1)
			return (NULL);
		else if (pid[counter] == 0)
			child_proc(counter, pipe_amount, fd, pid, shell, chain);
		else
		{
			if (parent_proc(counter, pipe_amount, fd, pid, line, buffer,
					bytesRead, m))
				break ;
		}
	}
	while (--pipe_amount >= 0)
	{
		close(fd[pipe_amount][0]);
		close(fd[pipe_amount][1]);
	}
	return (line);
}

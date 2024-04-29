/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:36:09 by jkauker           #+#    #+#             */
/*   Updated: 2024/03/25 15:51:15 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: check if this is correct even if we have somthing like echo "hello world""

char	*remove_surrounding_singleq(char *str, int *changed)
{
	if (!str || !*str
		|| (ft_strlen(str) == 2 && str[0] == '\'' && str[1] == '\''))
	{
		if (changed)
			*changed = 1;
		return (ft_strdup(""));
	}
	else if (ft_strlen(str) < 2)
	{
		if (changed)
			*changed = 1;
		return (str);
	}
	if (!str || !*str || (str[0] != '\'' && str[ft_strlen(str) - 1] != '\''))
		return (str);
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
	if (changed)
		*changed = 1;
	return (str);
}

char	*remove_surrounding_doubleq(char *str, int *changed)
{
	if (!str || !*str
		|| (ft_strlen(str) == 2 && str[0] == '"' && str[1] == '"'))
	{
		if (changed)
			*changed = 1;
		return (ft_strdup(""));
	}
	else if (ft_strlen(str) < 2)
	{
		if (changed)
			*changed = 1;
		return (str);
	}
	if (!str || !*str || (str[0] != '"' && str[ft_strlen(str) - 1] != '"'))
		return (str);
	ft_memmove(str, str + 1, ft_strlen(str) - 2);
	str[ft_strlen(str) - 2] = '\0';
	if (changed)
		*changed = 1;
	return (str);
}

bool	is_new_line(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (false);
	}
	return (true);
}

bool	is_valid_flag(char *str)
{
	if (str[0] != '-')
		return (false);
	str++;
	while (*str == 'n')
		str++;
	return (ft_isspace(*str) || *str == '\0');
}

char	*get_first(char *str)
{
	while (*str)
	{
		if (is_valid_flag(str))
		{
			while (*str != ' ' && *str != '\0')
				str++;
			while (ft_isspace(*str))
				str++;
		}
		else
			return (str);
	}
	return (str);
}

int	ft_echo(t_shunting_node *cmd)
{
	int		i;
	int		nl;
	int		c;

	i = -1;
	nl = 1;
	if (!cmd)
		return (CMD_FAILURE);
	while (cmd->args && cmd->args[++i]
		&& is_valid_flag(cmd->args[i]))
		nl = 0;
	i -= 2;
	if (i < -1)
		i = -1;
	c = i;
	while (cmd->args && cmd->args[++i])
	{
		if (c == i - 1)
		{
			if (cmd->args[i][0] != 0)
				printf("%s", get_first(cmd->args[i]));
			continue ;
		}
		else if (cmd->args[i][0] == '\0')
			printf(" ");
		else
			printf("%s", cmd->args[i]);
		if (cmd->args[i][0] != '\0' && cmd->args[i + 1])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (CMD_SUCCESS);
}

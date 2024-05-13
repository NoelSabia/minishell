/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:03:12 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/13 14:34:07 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_surrounding_doubleq(char *str, int *changed);

void	insert_str_on_pos_w_len(char **str, char *insert, int pos, int len)
{
	char	*new_str;
	int		i;
	int		k;

	new_str = malloc((ft_strlen(*str) + ft_strlen(insert) - len + 1)
			* sizeof(char));
	if (!new_str)
		return ;
	i = -1;
	k = 0;
	while ((*str)[++i])
	{
		if (i == pos)
			while (*insert)
				new_str[k++] = *insert++;
		if (i < pos || i >= pos + len)
			new_str[k++] = (*str)[i];
	}
	new_str[k] = '\0';
	free(*str);
	*str = new_str;
}

char	*append_single_char(char *str, char c)
{
	int		len;
	char	*out;

	if (!str)
	{
		out = malloc(2 * sizeof(char));
		if (!out)
			return (NULL);
		out[0] = c;
		out[1] = '\0';
	}
	else
	{
		len = ft_strlen(str);
		out = ft_realloc(str, (len + 2) * sizeof(char));
		if (!out)
			return (NULL);
		out[len] = c;
		out[len + 1] = '\0';
	}
	return (out);
}

char	*get_var_str(char *str)
{
	t_temps	temp;
	char	*var_str;
	char	*exit;
	char	*lol;

	temp.int_i = -1;
	temp.int_j = 0;
	var_str = NULL;
	if (!str)
		return (NULL);
	while (str && str[++temp.int_i])
	{
		if (str[temp.int_i] == '\'' || str[temp.int_i] == '"')
		{
			if (str[temp.int_i] == '\'')
			{
				temp.int_i++;
				while (str[temp.int_i] && str[temp.int_i] != '\'')
					var_str = append_single_char(var_str, str[temp.int_i++]);
				continue ;
			}
			temp.int_l = 0;
			while (str[temp.int_i])
			{
				if (temp.int_l == 0 && str[temp.int_i] == '"')
					temp.int_i++;
				if (temp.int_l++ != 0 && str[temp.int_i] == '"')
					break ;
				if (str[temp.int_i] != '$' && str[temp.int_i] != '"')
					var_str = append_single_char(var_str, str[temp.int_i++]);
				else if (str[temp.int_i] != '"')
				{
					if (str[temp.int_i + 1] && str[temp.int_i + 1] == '?')
					{
						exit = ft_itoa(*get_shell()->exit_status);
						if (!exit)
							return (NULL);
						var_str = ft_strjoin(var_str, exit);
						free(exit);
						if (!var_str)
							return (NULL);
						temp.int_i += 2;
						continue ;
					}
					temp.int_k = 1;
					while (str[temp.int_i + temp.int_k]
						&& ft_isalnum(str[temp.int_i + temp.int_k]))
						temp.int_k++;
					if (temp.int_k == 1 && str[temp.int_i + 1]
						&& (str[temp.int_i + temp.int_k] == '"' || str[temp.int_i + temp.int_k] == '\'' || str[temp.int_i + temp.int_k] == ' '))
					{
						var_str = append_single_char(var_str, str[temp.int_i++]);
						continue ;
					}
					temp.charp_i = ft_substr(str, temp.int_i, temp.int_k);
					if (!temp.charp_i)
						return (NULL);
					temp.env_var1 = env_get_by_name(get_shell()->env_vars,
							temp.charp_i + 1);
					free(temp.charp_i);
					if (temp.env_var1)
					{
						var_str = ft_strjoin(var_str, temp.env_var1->value);
						if (!var_str)
							return (NULL);
					}
					temp.int_i += temp.int_k;
				}
			}
		}
		else
		{
			if (str[temp.int_i] != '$')
			{
				var_str = append_single_char(var_str, str[temp.int_i]);
				if (!var_str)
					return (NULL);
				continue ;
			}
			if (str[temp.int_i + 1] && str[temp.int_i + 1] == '?')
			{
				exit = ft_itoa(*get_shell()->exit_status);
				if (!exit)
					return (NULL);
				var_str = ft_strjoin(var_str, exit);
				free(exit);
				if (!var_str)
					return (NULL);
				temp.int_i++;
				continue ;
			}
			if (!str[temp.int_i + 1])
			{
				var_str = append_single_char(var_str, str[temp.int_i]);
				if (!var_str)
					return (NULL);
				continue ;
			}
			temp.int_k = 1;
			while (str[temp.int_i + temp.int_k]
				&& ft_isalnum(str[temp.int_i + temp.int_k]))
				temp.int_k++;
			if (temp.int_k == 1 && str[temp.int_i + 1]
				&& (str[temp.int_i + temp.int_k] == '"'
					|| str[temp.int_i + temp.int_k] == '\'' || str[temp.int_i + temp.int_k] == ' '))
				continue ;
			temp.charp_i = ft_substr(str, temp.int_i, temp.int_k);
			if (!temp.charp_i)
				return (NULL);
			temp.env_var1 = env_get_by_name(get_shell()->env_vars,
					temp.charp_i + 1);
			free(temp.charp_i);
			if (temp.env_var1)
			{
				if (ft_isspace(temp.env_var1->value[0]) &&
					ft_isspace(temp.env_var1->value[ft_strlen(temp.env_var1->value) - 1]))
				{
					lol = ft_strtrim(temp.env_var1->value, " \t\n\r\v\f");
					lol = ft_strjoin(" ", ft_strjoin(lol, " "));
					var_str = ft_strjoin(var_str, lol);
				}
				else
					var_str = ft_strjoin(var_str, temp.env_var1->value);
				if (!var_str)
					return (NULL);
			}
			temp.int_i += temp.int_k - 1;
		}
	}
	if (str)
		free(str);
	return (var_str);
}

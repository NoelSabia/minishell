/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:22:09 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/16 08:02:57 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_free_many(void *return_val, int count, ...)
{
	va_list	args;
	void	*ptr;

	va_start(args, count);
	while (count--)
	{
		ptr = va_arg(args, void *);
		if (ptr)
		{
			ft_free((ptr));
		}
	}
	va_end(args);
	return (return_val);
}

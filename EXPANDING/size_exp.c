/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:34:53 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 00:19:58 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*******ALLOCATTION STR WITH LENGTH OF VAR VALUES*****************************/

#include "../minishell.h"

int	len(char *str, t_data *env)
{
	t_var	var;

	var.tmp = (char *)calloc(ft_strlen(str) + 1, 1);
	var.i = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\'' || *str == '\"' || *str == '$')
			break ;
		var.tmp[var.i++] = *str;
		str++;
	}
	if (!*var.tmp)
		return (free(var.tmp), 0);
	var.len = ft_strlen(var.tmp);
	while (env)
	{
		if (!ft_strncmp(env->variable, var.tmp, var.len))
		{
			var.i = ft_strlen(env->value);
			break ;
		}
		env = env->next;
	}
	return (free(var.tmp), var.i);
}

int	allocation(char *str, t_data *env)
{
	int	i;

	i = ft_strlen(str);
	while (*str)
	{
		if (*str == '$' && *(str + 1) && *(str + 1) != '$')
			i += len(++str, env);
		str++;
	}
	return (i);
}

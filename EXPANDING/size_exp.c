/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:34:53 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 21:51:28 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*******ALLOCATTION STR WITH LENGTH OF VAR VALUES*****************************/

#include "../minishell.h"

int	len(char *str, t_data *env)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = (char *)calloc(ft_strlen(str) + 1, 1);
	i = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\'' || *str == '\"' || *str == '$')
			break ;
		tmp[i++] = *str++;
	}
	if (!*tmp)
		return (free(tmp), 0);
	len = ft_strlen(tmp);
	while (env)
	{
		if (!ft_strncmp(env->variable, tmp, len))
		{
			i = ft_strlen(env->value);
			break ;
		}
		env = env->next;
	}
	return (free(tmp), i);
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

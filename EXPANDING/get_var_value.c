/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:49 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 22:37:12 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

char	*var_search(t_data *env, char *tmp, int len)
{
	int	i;

	i = -1;
	while (env)
	{
		if (!ft_strncmp(env->variable, tmp, len))
		{
			if (!*env->value)
				return (free(tmp), NULL);
			free(tmp);
			tmp = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!env)
		return (free(tmp), ft_strdup("\0"));
	return (tmp);
}

char	*get_var_value(char *str, int *x, t_data *env)
{
	char	*tmp;
	int		i;
	int		len;

	tmp = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	while (str[++(*x)])
	{
		if (str[(*x)] == '?')
		{
			++(*x);
			return (free(tmp), ft_itoa(g_status));
		}
		if (str[*x] == ' ' || str[*x] == '\"' \
		|| str[*x] == '\'' || str[*x] == '$')
			break ;
		tmp[i++] = str[*x];
	}
	if (!*tmp)
		return (tmp);
	len = ft_strlen(tmp);
	tmp = var_search(env, tmp, len);
	return (tmp);
}

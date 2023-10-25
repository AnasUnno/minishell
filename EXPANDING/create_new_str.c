/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:45:49 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/22 20:36:49 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bring_dequoted_value(char *str, int i, char *s, int j)
{
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		s[j++] = str[i];
		i++;
	}
	return (i);
}

int	create_new_str(char *str, char *s, int i, t_data *env)
{
	int		j;
	char	*tmp;

	j = ft_strlen(s);
	if (str[i - 1] == '\'')
		i = bring_dequoted_value(str, i, s, j);
	else
	{
		while (str[i])
		{
			if (str[i] == '\"')
				break ;
			if (str[i] == '$')
			{
				tmp = get_var_value(str, &i, env, 0);
				while (*tmp)
					s[j++] = *tmp++;
				continue ;
			}
			s[j++] = str[i];
			i++;
		}
	}
	return (i);
}

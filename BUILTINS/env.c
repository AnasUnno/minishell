/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:07:13 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/19 18:19:12 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_start_end(char *str, int *lenght1, int *lenght2)
{
	while (str[*lenght1] && str[*lenght1] != '=')
		(*lenght1)++;
	*lenght2 = *lenght1 + 1;
	while (str[*lenght2])
		(*lenght2)++;
}

void	get_environement(char **env, t_data **environement)
{
	int		lenght1;
	int		lenght2;
	int		i;
	t_data	*tmp;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
	{
		lenght1 = 0;
		lenght2 = 0;
		get_start_end(env[i], &lenght1, &lenght2);
		if (!(*environement))
			(*environement) = ft_mylstnew(ft_substr(env[i], 0, lenght1),
					ft_substr(env[i], lenght1 + 1, lenght2));
		else
		{
			tmp = ft_mylstnew(ft_substr(env[i], 0, lenght1),
					ft_substr(env[i], lenght1 + 1, lenght2));
			ft_lstadd_back(environement, tmp);
			tmp = NULL;
		}
	}
	reset_old_pwd(environement);
}

void	reset_old_pwd(t_data **envi)
{
	t_data	*tmp;

	tmp = *envi;
	while (tmp)
	{
		if (!my_strcmp(tmp->variable, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int	env(t_data *envi)
{
	while (envi)
	{
		if (envi->value)
		{
			printf("%s", envi->variable);
			printf("=");
			printf("%s\n", envi->value);
		}
		envi = envi->next;
	}
	return (0);
}

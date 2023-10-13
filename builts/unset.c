/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:08:19 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/13 14:59:00 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_unset_params(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '_' || ft_isalpha((int)str[i]))
	{
		i++;
		while (str[i])
		{
			if (str[i] != '_' && !ft_isalnum((int)str[i]))
			{
				ft_printf("Minishell: unset: `%s': not a valid identifier\n",
					str);
				return (0);
			}
			i++;
		}
		return (1);
	}
	else
	{
		ft_printf("Minishell: unset: `%s': not a valid identifier\n", str);
		return (0);
	}
}

t_data	*get_variable(t_data *envi, char *str)
{
	while (envi)
	{
		if (!ft_strcmp(envi->variable, str))
			return (envi);
		envi = envi->next;
	}
	return (NULL);
}

int	check_pos(t_data *envi, t_data *tmp)
{
	if (tmp == ft_lstlast(envi))
		return (0);
	else if (tmp == envi)
		return (1);
	return (-1);
}

t_data	*get_before(t_data *envi, t_data *tmp)
{
	while (envi)
	{
		if (envi->next == tmp || !envi->next)
			return (envi);
		envi = envi->next;
	}
	return (envi);
}

void	unset(char **av, t_data **environement)
{
	int		i;
	t_data	*tmp;
	t_data	*tmp2;

	i = 0;
	while (av[i])
	{
		if (!check_unset_params(av[i]))
			i++;
		else
		{
			tmp = get_variable(*environement, av[i]);
			if (!tmp || !*environement)
				return ;
			if (check_pos(*environement, tmp) == 1)
				first_on(&tmp, environement);
			else if (check_pos(*environement, tmp) == 0)
				last_on(&tmp2, &tmp, environement);
			else
				in_middle(&tmp2, &tmp, environement);
			i++;
		}
	}
}

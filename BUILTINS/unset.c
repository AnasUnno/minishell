/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:08:19 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/31 12:10:33 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset_params(char *str, int *status)
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
				return (*status = 1, 0);
			}
			i++;
		}
		return (1);
	}
	else
	{
		ft_printf("Minishell: unset: `%s': not a valid identifier\n", str);
		return (*status = 1, 0);
	}
}

t_data	*get_variable(t_data *envi, char *str)
{
	while (envi)
	{
		if (!my_strcmp(envi->variable, str))
			return (envi);
		envi = envi->next;
	}
	return (NULL);
}

int	check_pos(t_data *envi, t_data *tmp)
{
	if (!envi)
		return (3);
	if (tmp == ft_lstlast(envi) && ft_lstsize(envi) > 1)
		return (0);
	else if (tmp == envi)
		return (1);
	else if (tmp)
		return (2);
	return (4);
}

t_data	*get_before(t_data *envi, t_data *tmp)
{
	while (envi)
	{
		if (envi->next == tmp || !envi->next)
			return (envi);
		envi = envi->next;
	}
	return (NULL);
}

int	unset(char **av, t_data **environement)
{
	int		i;
	t_data	*tmp;
	t_data	*tmp2;
	int		status;

	i = 0;
	status = 0;
	while (av[i])
	{
		if (!check_unset_params(av[i], &status))
			i++;
		else
		{
			tmp = get_variable(*environement, av[i]);
			if (check_pos(*environement, tmp) == 1)
				first_on(&tmp, environement);
			else if (check_pos(*environement, tmp) == 0)
				last_on(&tmp2, &tmp, environement);
			else if (check_pos(*environement, tmp) == 2)
				in_middle(&tmp2, &tmp, environement);
			i++;
		}
	}
	return (status);
}

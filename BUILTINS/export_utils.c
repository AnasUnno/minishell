/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:37:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/30 18:41:48 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_args(char *str, int *status)
{
	int	i;

	i = 0;
	if (str[i] == '_' || ft_isalpha((int)str[i]))
	{
		i++;
		while (str[i] && str[i] != '=' && str[i] != '+')
		{
			if (str[i] != '_' && !ft_isalnum((int)str[i]))
			{
				ft_printf("Minishell: export: `%s': not a valid identifier\n", str);
				return (*status = 1, 0);
			}
			i++;
		}
		if (str[i] == '+' && str[i + 1] != '=')
		{
			ft_printf("Minishell: export: `%s': not a valid identifier\n", str);
			return (*status = 1, 0);
		}
		return (1);
	}
	ft_printf("Minishell: export: `%s': not a valid identifier\n", str);
	return (*status = 1, 0);
}

int	get_var_lenght(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	return (i);
}

int	get_value_lenght(int end, char *str)
{
	if (str[end] == '+')
		end += 2;
	else if (str[end] == '=')
		end++;
	while (str[end])
		end++;
	return (end);
}

int	check_append_new(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '=' && str[i - 1] == '+')
		return (1);
	if (str[i] == '=' && str[i - 1] != '+')
		return (2);
	return (-1);
}

void	create_new_var(t_export *exp, char *av, t_data **envi)
{
	if (!exp->tmp)
	{
		exp->tmp = ft_mylstnew(av, NULL);
		if (!envi || !*envi)
			*envi = exp->tmp;
		else
			ft_lstadd_back(envi, exp->tmp);
	}
}

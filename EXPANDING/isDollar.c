/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isDollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:15 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 21:50:30 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1])
			return (1);
	}
	return (0);
}

void	expander_for_dollar(t_tree *tree, t_v *v, t_data *env)
{
	tree->strs[v->i] = clean_str(tree->strs[v->i], env, tree);
	if (tree->strs[v->i])
	{
		if (tree->flag)
		{
			v->y = -1;
			v->tmp = ft_strtok(tree->strs[v->i]);
			while (v->tmp && v->tmp[++v->y])
			{
				free(v->strs[v->j]);
				v->strs[v->j++] = ft_strdup(v->tmp[v->y]);
			}
			free_all(v->tmp);
		}
		else
		{
			free(v->strs[v->j]);
			v->strs[v->j++] = ft_strdup(tree->strs[v->i]);
		}
	}
}

void	dollar_valid(t_tree *tree, t_v *v, t_data *env)
{
	tree->flag = 0;
	if (check_dollar(tree->strs[v->i]))
		expander_for_dollar(tree, v, env);
	else
	{
		tree->strs[v->i] = remove_quotes(tree->strs[v->i]);
		if (v->strs[v->j])
			free(v->strs[v->j]);
		v->strs[v->j++] = ft_strdup(tree->strs[v->i]);
	}
}

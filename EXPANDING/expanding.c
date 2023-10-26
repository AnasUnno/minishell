/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:21:09 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/24 00:04:48 by kzerri           ###   ########.fr       */
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

void	push_to_s(char *tmp, int j, char *str, char *s)
{
	if (!tmp)
		return ;
	if (s[j - 1] && s[j - 1] != ' ' && *tmp == ' ')
		s[j++] = *tmp++;
	else if (*tmp == ' ')
		tmp++;
	while (*tmp)
		s[j++] = *tmp++;
	if ((*str == ' ' || !*str) && *(tmp - 1) == ' ')
		s[j - 1] = 0;
}

int	flag(t_tree *tree)
{
	return (tree->flag = 1);
}

char	*clean_str(char *str, t_data *env, t_tree *tree)
{
	t_var	var;

	var.j = allocation(str, env);
	var.s = (char *)ft_calloc(var.j + 1, 1);
	var.i = 0;
	while (str[var.i])
	{
		var.j = ft_strlen(var.s);
		if (str[var.i] == '\'')
			var.i = create_new_str(str, var.s, var.i + 1, env);
		else if (str[var.i] == '\"')
			var.i = create_new_str(str, var.s, var.i + 1, env);
		else if (str[var.i] == '$' && flag(tree))
		{
			var.tmp = get_var_value(str, &var.i, env, 1);
			push_to_s(var.tmp, var.j, &str[var.i], var.s);
			if (var.tmp && *var.tmp)
				free(var.tmp);
			continue ;
		}
		else
			var.s[var.j++] = str[var.i];
		var.i++;
	}
	return (var.s);
}

void	expand(t_tree *tree, t_data *env, char **environement)
{
	int		i;

	i = -1;
	while (tree->strs[++i])
		;
	tree->count = i;
	i = -1;
	while (tree->strs[++i])
	{
		tree->flag = 0;
		if (check_dollar(tree->strs[i]))
			tree->strs[i] = clean_str(tree->strs[i], env, tree);
		else
			tree->strs[i] = remove_quotes(tree->strs[i]);
	}
}

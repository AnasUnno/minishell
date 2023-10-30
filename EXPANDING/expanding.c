/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:21:09 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 02:52:54 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_to_s(char *tmp, int j, char *str, char *s)
{
	char	*fr;

	fr = tmp;
	if (!tmp)
		return ;
	if (j >= 1 && s[j - 1] && s[j - 1] != ' ' && *tmp == ' ')
		s[j++] = *tmp++;
	else if (*tmp == ' ')
		tmp++;
	while (*tmp)
		s[j++] = *tmp++;
	if (*str && (*str == ' ' || !*str) && *(tmp - 1) == ' ')
		s[j - 1] = 0;
	free_var(fr);
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
			var.tmp = get_var_value(str, &var.i, env);
			push_to_s(var.tmp, var.j, &str[var.i], var.s);
			continue ;
		}
		else
			var.s[var.j++] = str[var.i];
		var.i++;
	}
	return (free_var(str), var.s);
}

void	expand(t_tree *tree, t_data *env, char **environement)
{
	t_v	v;

	v.i = -1;
	while (tree->strs[++v.i])
		;
	v.c = -1;
	while (tree->strs[++v.c])
		v.len += allocation(tree->strs[v.c], env);
	v.strs = (char **)ft_calloc((v.i * v.len) + 1, sizeof(char *));
	v.i = -1;
	v.j = 0;
	while (tree->strs[++v.i])
		dollar_valid(tree, &v, env);
	free_all(tree->strs);
	tree->strs = v.strs;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/19 15:30:30 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left);
	free_all(tree->strs);
	free(tree);
	free_tree(tree->right);
}

char	*final_str(char *str)
{
	char	*final;
	char	*operators;
	int		index;
	int		size;
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	free(str);
	str = NULL;
	size = ft_strlen(tmp);
	operators = "<|>";
	final = ft_calloc((size * 2) + 1, 1);
	index = 0;
	if (!final)
		return (NULL);
	while (*tmp && index < size * 2)
	{
		if (!ft_strchr(operators, *tmp))
			final[index++] = *tmp++;
		else
			process_operator(&final, &tmp, &index);
	}
	return (final);
}

int	count_words(char *str)
{
	int		count;
	int		in_quote;
	char	c;

	count = 0;
	in_quote = 0;
	while (*str)
		count_word_helper(&str, &in_quote, &c, &count);
	if (!in_quote)
		count++;
	return (count);
}

char	**ft_split2(char *str)
{
	t_vars	var;

	var.white_spaces = " \t\n";
	helper(&var.in_quote, &var.i, &var.j, &var.start);
	var.count = count_words(str);
	var.splited = (char **)malloc(sizeof(char *) * (var.count + 1));
	while (str[var.i])
	{
		if ((str[var.i] == '\'' || str[var.i] == '\"') && !var.in_quote)
			helper3(str, &var.in_quote, &var.i, &var.c);
		else if (str[var.i] == var.c && var.in_quote)
			helper4(&var.in_quote, &var.i, &var.c);
		else if (ft_strchr(var.white_spaces, str[var.i]) && !var.in_quote)
			var.splited[var.j++] = helper2(str, &var.i, &var.start);
		else
			var.i++;
	}
	if (!var.in_quote)
	{
		var.splited[var.j] = (char *)malloc(sizeof(char) \
			* ((var.i - var.start) + 1));
		ft_strncpy(var.splited[var.j++], &str[var.start], var.i - var.start);
	}
	return (var.splited[var.j] = NULL, var.splited);
}

int main(int ac, char **av, char **env)
{
	char	*cmd; 
	char	**command;
	char	*final;
	t_tree	*tree;
	t_data	*envi;

	envi = NULL;
	get_environement(env, &envi);
	// rl_initialize();
	// rl_catch_signals = 0;
	while(1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("$Minishell: ");
		if (!cmd)
			break;
		add_history(cmd);
		if (!*cmd || !is_valide(cmd))
			continue;
		final = final_str(cmd);
		command = ft_split2(final);
		tree = NULL;
		level1(&tree, command, 0);
		execute(tree, envi, env);
	}
	free_tree(tree);
}

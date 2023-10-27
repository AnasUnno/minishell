/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/27 17:53:49 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_final(char **final, char **tmp, int *index, char *operators)
{
	char	c;
	char	*oprators;

	c = 0;
	if (ft_strchr("'\'\"", *(*tmp)))
	{
		c = *(*tmp);
		(*final)[(*index)++] = *(*tmp)++;
		while (*tmp && *(*tmp) != c)
			(*final)[(*index)++] = *(*tmp)++;
		(*final)[(*index)++] = *(*tmp)++;
	}
	else if (ft_strchr(operators, *(*tmp)))
	{
		if (*(*tmp) == '>' || *(*tmp) == '<')
			process_operator(final, tmp, index);
		else
		{
			(*final)[(*index)++] = ' ';
			(*final)[(*index)++] = *(*tmp)++;
			(*final)[(*index)++] = ' ';
		}
	}
	else
		(*final)[(*index)++] = *(*tmp)++;
}

char	*final_str(char *str)
{
	char	*final;
	char	*operators;
	int		index;
	int		size;
	char	*tmp;

	tmp = ft_strtrim(str, " \t\n");
	free(str);
	str = NULL;
	size = ft_strlen(tmp);
	operators = "<|>";
	final = ft_calloc((size * 2) + 1, 1);
	index = 0;
	if (!final)
		return (NULL);
	while (*tmp && index < size * 2)
		fill_final(&final, &tmp, &index, operators);
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
	var.trimmed = ft_strtrim(str, " \t");
	free(str);
	var.count = count_words(var.trimmed);
	var.splited = (char **)malloc(sizeof(char *) * (var.count + 1));
	while (var.trimmed[var.i])
	{
		if ((var.trimmed[var.i] == '\'' || var.trimmed[var.i] == '\"') && !var.in_quote)
			helper3(var.trimmed, &var.in_quote, &var.i, &var.c);
		else if (var.trimmed[var.i] == var.c && var.in_quote)
			helper4(&var.in_quote, &var.i, &var.c);
		else if (ft_strchr(var.white_spaces, var.trimmed[var.i]) && !var.in_quote)
			var.splited[var.j++] = helper2(var.trimmed, &var.i, &var.start);
		else
			var.i++;
	}
	if (!var.in_quote)
	{
		var.splited[var.j] = (char *)malloc(sizeof(char) \
			* ((var.i - var.start) + 1));
		ft_strncpy(var.splited[var.j++], &var.trimmed[var.start], var.i - var.start);
	}
	var.splited[var.j] = NULL;
	return (free(var.trimmed), var.splited);
}

void	handler(int num)
{
	int		fd[2];

	rl_replace_line("", 0);
	pipe(fd);
	dup2(fd[0], STDIN_FILENO);
	ft_putstr_fd("\n", fd[1]);
	close(fd[0]);
	close(fd[1]);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;
	int		c;

	var.envi = NULL;
	var.fdbackup = dup(STDIN_FILENO);
	get_environement(env, &var.envi);
	rl_catch_signals = 0;
	while (1)
	{
		dup2(var.fdbackup, STDIN_FILENO);
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		var.cmd = readline("$Minishell: ");
		if (!var.cmd)
			break ;
		if (!*var.cmd)
		{
			free(var.cmd);
			continue ;
		}
		add_history(var.cmd);
		if (!*var.cmd || !is_valide(var.cmd))
		{
			free(var.cmd);
			continue ;
		}
		var.final = final_str(var.cmd);
		var.command = ft_split2(var.final);
		// for(int i = 0; var.command[i]; i++)
		// {
		// 	printf("| |\n");
		// 	printf("|%s|\n", var.command[i]);
		// }
		// free(var.final);
		var.tree = NULL;
		level1(&var.tree, var.command, 0);
		execute(var.tree, var.envi, env);
		free_tree(var.tree);
		free_splited(var.command);
		// free(var.cmd);
	}
	free_env(&var.envi);
	rl_clear_history();
	return (0);
}

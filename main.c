/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/30 18:45:37 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str = tmp;
	size = ft_strlen(tmp);
	operators = "<|>";
	final = ft_calloc((size * 2) + 1, 1);
	index = 0;
	if (!final)
		return (NULL);
	while (*tmp && index < size * 2)
		fill_final(&final, &tmp, &index, operators);
	return (free(str), final);
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
			continue ;
		var.final = final_str(var.cmd);
		var.command = ft_split2(var.final);
		var.tree = NULL;
		level1(&var.tree, var.command, 0);
		if (get_herdoc_file_name(var.tree, var.envi) == -1)
		{
			g_status = 1;
			free_tree(var.tree);
			continue ;
		}
		execute(var.tree, &var.envi, env);
		free_tree(var.tree);
		free_all(var.command);
	}
	close(var.fdbackup);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/03 00:07:45 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int num)
{
	int		fd[2];

	rl_replace_line("", 0);
	pipe(fd);
	dup2(fd[0], STDIN_FILENO);
	ft_putstr_fd("\n", fd[1]);
	close(fd[0]);
	close(fd[1]);
	g_status = 1;
}

void	initialize_var(t_var *var, char **env)
{
	var->envi = NULL;
	var->fdbackup = dup(STDIN_FILENO);
	get_environement(env, &var->envi);
	rl_catch_signals = 0;
}

void	prepare_minishell(t_var *var)
{
	dup2(var->fdbackup, STDIN_FILENO);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	var->cmd = readline("$Minishell: ");
}

int	read_and_validate_command(t_var *var)
{
	if (!*var->cmd)
	{
		free(var->cmd);
		return (1);
	}
	if (!is_valide(var->cmd))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	initialize_var(&var, env);
	while (1)
	{
		prepare_minishell(&var);
		if (!var.cmd)
			break ;
		add_history(var.cmd);
		if (read_and_validate_command(&var))
			continue ;
		var.final = final_str(var.cmd);
		var.command = ft_split2(var.final);
		var.tree = NULL;
		level1(&var.tree, var.command, 0);
		if (get_herdoc_file_name(var.tree, var.envi) == -1)
		{
			g_status = 1;
			cleanup(&var, 0);
			continue ;
		}
		execute(var.tree, &var.envi, env);
		cleanup(&var, 0);
	}
	cleanup(&var, 1);
}

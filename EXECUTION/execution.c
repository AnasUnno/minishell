/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:20:38 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 15:11:45 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_execute(t_tree *tree, t_data *envi, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_er_fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!tree->strs[0])
			exit(0);
		if (ft_strchar(tree->strs[0], '/'))
			tree->strs[0] = get_cmd(tree->strs[0], envi);
		execve(tree->strs[0], tree->strs, env);
		puts(strerror(errno));
		exit(1);
	}
	waitpid(pid, &g_status, 0);
	g_status = check_exit_state(g_status);
}

void	check_builtin(t_tree *tree, t_data **envi, char **environement)
{
	if (tree->strs[0] && ft_strcmp(tree->strs[0], "echo"))
		g_status = echo(&tree->strs[1]);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "cd"))
		g_status = cd(tree->strs[1], envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "pwd"))
		g_status = pwd();
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "export"))
		g_status = export(&tree->strs[1], envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "unset"))
		g_status = unset(&tree->strs[1], envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "env"))
		g_status = env(*envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "exit"))
		g_status = ft_exit(&tree->strs[1]);
	else
		cmd_execute(tree, *envi, environement);
}

void	execute(t_tree *tree, t_data **env, char **environement)
{
	if (!tree)
		return ;
	if (ft_strcmp(tree->strs[0], "|"))
		ft_pipe(tree, *env, environement);
	else if (ft_strcmp(tree->strs[0], "<"))
		ft_left_red(tree, *env, environement);
	else if (ft_strcmp(tree->strs[0], ">"))
		ft_right_red(tree, *env, environement);
	else if (ft_strcmp(tree->strs[0], "<<"))
		ft_left_red(tree, *env, environement);
	else if (ft_strcmp(tree->strs[0], ">>"))
		ft_r_double_red(tree, *env, environement);
	else
	{
		expand(tree, *env, environement);
		check_builtin(tree, env, environement);
	}
}

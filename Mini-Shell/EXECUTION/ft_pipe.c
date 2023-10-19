/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:37:47 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/18 15:38:53 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	left(t_tree *tree, int fds[2], t_data *envi, char **env)
{
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	execute(tree->left, envi, env);
	exit(0);
}

void	right(t_tree *tree, int fds[2], t_data *envi, char **env)
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[1]);
	close(fds[0]);
	execute(tree->right, envi, env);
	exit(0);
}

void	ft_pipe(t_tree *tree, t_data *envi, char **env)
{
	int	fds[2];
	int	pid1;
	int	pid2;

	if (pipe(fds) < 0)
		exit(1);
	pid1 = fork();
	if (!pid1)
		left(tree, fds, envi, env);
	pid2 = fork();
	if (!pid2)
		right(tree, fds, envi, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, &g_status, 0);
	waitpid(pid2, &g_status, 0);
}

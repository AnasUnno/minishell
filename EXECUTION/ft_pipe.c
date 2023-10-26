/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:37:47 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/23 18:44:35 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit_state(int state)
{
	if (WIFSIGNALED(state))
	{
		if (WTERMSIG(state) == SIGQUIT)
		{
			printf("QUIT: ");
			printf("%d", WTERMSIG(state));
			printf("\n");
		}
		else if (WTERMSIG(state) == SIGINT)
			printf("\n");
		return (128 + WTERMSIG(state));
	}
	return (WEXITSTATUS(state));
}

void	sig_handler(int signal)
{
	check_exit_state(signal);
}

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
	g_status = check_exit_state(g_status);
	waitpid(pid2, &g_status, 0);
	g_status = check_exit_state(g_status);
}

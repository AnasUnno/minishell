/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:05 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/31 17:50:26 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_left_red(t_tree *tree, t_data *envi, char **env)
{
	int	fd;
	int	backup_fd;

	if (expand_redir(tree->right, envi, env))
		return ;
	backup_fd = dup(STDIN_FILENO);
	fd = open(tree->right->strs[0], O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(tree->right->strs[0]);
		g_status = 1;
		close(backup_fd);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	execute(tree->left, &envi, env);
	dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
	close(fd);
}

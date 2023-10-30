/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:05 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/30 18:48:55 by araji-af         ###   ########.fr       */
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
		return ;
	}
	dup2(fd, STDIN_FILENO);
	execute(tree->left, &envi, env);
	dup2(backup_fd, STDIN_FILENO);
	close(backup_fd);
	close(fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:02 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/23 16:36:52 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_right_red(t_tree *tree, t_data *envi, char **env)
{
	int	fd;
	int	backup_fd;

	if (expand_redir(tree->right, envi, env))
		return ;
	backup_fd = dup(STDOUT_FILENO);
	fd = open(tree->right->strs[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(tree->right->strs[0]);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	execute(tree->left, envi, env);
	dup2(backup_fd, STDOUT_FILENO);
}

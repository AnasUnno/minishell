/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:05 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/18 16:05:11 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_left_red(t_tree *tree, t_data *envi, char **env)
{
	int	fd;
	int	backup_fd;

	backup_fd = dup(STDIN_FILENO);
	fd = open(tree->right->strs[0], O_RDONLY, 0644);
	if (fd < 0)
	{
		perror(tree->right->strs[0]);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	execute(tree->left, envi, env);
	dup2(backup_fd, STDIN_FILENO);
}

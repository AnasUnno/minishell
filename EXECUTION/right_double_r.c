/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_double_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:08 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/23 16:31:50 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_redir(t_tree *tree, t_data *envi, char **env)
{
	char	*s;

	s = ft_strdup(tree->strs[0]);
	expand(tree, envi, env);
	if (tree->flag && !tree->strs[0][0])
	{
		ft_printf("minishell: %s: ambiguous redirect\n", s);
		g_status = 1;
		return (1);
	}
	if (!tree->strs[0][0])
	{
		ft_printf("bash: : No such file or directory\n");
		g_status = 1;
		return (1);
	}
	return (0);
}

void	ft_r_double_red(t_tree *tree, t_data *envi, char **env)
{
	int		fd;
	int		backup_fd;

	if (expand_redir(tree->right, envi, env))
		return ;
	backup_fd = dup(STDOUT_FILENO);
	fd = open(tree->right->strs[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(tree->right->strs[0]);
		g_status = 1;
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	execute(tree->left, envi, env);
	dup2(backup_fd, STDOUT_FILENO);
}

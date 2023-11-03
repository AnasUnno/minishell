/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_double_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:08 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/31 17:49:48 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ambiguous_double(t_tree *tree, char *s)
{
	int	i;

	i = -1;
	while (tree->strs[++i])
		;
	if (i > 1)
	{
		ft_printf("minishell: %s: ambiguous redirect\n", s);
		g_status = 1;
		return (1);
	}
	return (0);
}

int	expand_redir(t_tree *tree, t_data *envi, char **env)
{
	char	*s;

	s = ft_strdup(tree->strs[0]);
	expand(tree, envi, env);
	if (tree->flag && !tree->strs[0])
	{
		ft_printf("minishell: %s: ambiguous redirect\n", s);
		g_status = 1;
		return (free(s), 1);
	}
	if (!*tree->strs[0])
	{
		ft_printf("minishell: : No such file or directory\n");
		g_status = 1;
		return (free(s), 1);
	}
	if (ambiguous_double(tree, s))
		return (free(s), 1);
	return (free(s), 0);
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
		close(backup_fd);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	execute(tree->left, &envi, env);
	dup2(backup_fd, STDOUT_FILENO);
	close(backup_fd);
	close(fd);
}

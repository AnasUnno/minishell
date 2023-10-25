/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:02:42 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/24 22:29:43 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_node(t_tree **node, char *s)
{
	*node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		exit(1);
	(*node)->left = NULL;
	(*node)->right = NULL;
	if (!s)
		return ;
	(*node)->strs = (char **)calloc(2, sizeof(char *));
	(*node)->strs[0] = ft_strdup(s);
}

char	**level3(char **strs, char **cmd, int start)
{
	int		i;
	int		j;
	int		end;

	i = start;
	end = start;
	while (strs[i])
	{
		if (strs[i][0] == '<' || strs[i][0] == '>')
			i++;
		else
			end++;
		i++;
	}
	cmd = (char **)calloc((end - start) + 1, sizeof(char *));
	j = -1;
	i = start - 1;
	while (strs[++i])
	{
		if (strs[i][0] == '<' || strs[i][0] == '>')
			i++;
		else
			cmd[++j] = ft_strdup(strs[i]);
	}
	return (cmd);
}

void	level2(t_tree **tree, char **strs, int start, char **cmd)
{
	int		i;

	i = start;
	if (!cmd)
		cmd = level3(strs, cmd, start);
	while (strs[i])
	{
		if (strs[i][0] == '<' || strs[i][0] == '>')
		{
			create_node(tree, strs[i]);
			create_node(&(*tree)->right, NULL);
			(*tree)->right->strs = (char **)ft_calloc(2, sizeof(char *));
			(*tree)->right->strs[0] = ft_strdup(strs[i + 1]);
			level2(&(*tree)->left, strs, i + 2, cmd);
			return ;
		}
		i++;
	}
	if (*cmd[0])
	{
		create_node(tree, NULL);
		(*tree)->strs = cmd;
	}
}

void	level1(t_tree **tree, char **strs, int start)
{
	int	i;

	i = start;
	while (strs[i])
	{
		if (ft_strcmp("|", strs[i]))
		{
			create_node(tree, strs[i]);
			free(strs[i]);
			strs[i] = NULL;
			level2(&(*tree)->left, strs, start, NULL);
			level1(&(*tree)->right, strs, i + 1);
			return ;
		}
		i++;
	}
	level2(tree, strs, start, NULL);
	return ;
}

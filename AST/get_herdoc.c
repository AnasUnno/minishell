/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:54:03 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 21:37:11 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_herdoc_file_name(t_tree *tree, t_data *envi)
{
	if (!tree)
		return (0);
	if (ft_strcmp(tree->strs[0], "<<"))
		ft_l_double_red(tree, envi);
	if (g_status == -1)
		return (-1);
	get_herdoc_file_name(tree->left, envi);
	if (g_status == -1)
		return (-1);
	return (0);
}

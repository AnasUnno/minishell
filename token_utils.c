/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:51:18 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/23 13:55:45 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_carac(char c)
{
	if ((c == '|' || c == '>' || c == '<'))
		return (1);
	return (0);
}

void	helper(char c, int space_count, int count, int flag)
{
	if (c != ' ')
		{
			count++;
			flag = 1;
		}
		else if (c == ' ' && flag)
		{
			space_count++;
			flag = 0;
		}
}

int	count_str(char *str)
{
	int			i;
	int		space_count;
	int		count;
	int		flag;

	i = 0;
	space_count = 0;
	count = 0;
	flag = 0;
	str = ft_strtrim(str, " ");
	while (str[i])
	{
		helper(str[i], space_count, count, flag);
		i++;
	}
	return (count + space_count);
}
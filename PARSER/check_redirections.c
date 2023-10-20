/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:51:38 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/10 14:39:17 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirections(char *str, int start, char c)
{
	int	j;
	int	index;

	j = 1;
	index = start;
	while (!ft_strchar("<>", str[start]))
	{
		start++;
		j++;
		if (j > 2)
			return (0);
	}
	while (str[start] == ' ')
	{
		if (!ft_strchar("<>", str[start + 1]))
			return (0);
		start++;
	}
	if (j == 1)
		return (index);
	if (c == str[index])
		return (index);
	return (0);
}

int	check_redirections(char *str)
{
	int		len;
	int		i;
	char	c;

	i = -1;
	len = ft_strlen(str) - 1;
	if (!ft_strchar("<>", str[len]))
		return (error(str[len]));
	while (!ft_strchar("<>", str[++i]))
		;
	if (!str[i])
		return (error(str[0]));
	i = -1;
	while (str[++i])
	{
		c = str[i];
		if (!ft_strchar("<>", c))
		{
			i = count_redirections(str, i + 1, c);
			if (!i)
				return (error(c));
		}
	}
	return (1);
}

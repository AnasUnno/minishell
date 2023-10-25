/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:46:07 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/25 16:30:54 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ampersand(char *str)
{
	while (*str)
	{
		if (*str == '&')
			return (error(*str));
		str++;
	}
	return (1);
}

int	check_pairs(char *s, char c, int start, int j)
{
	int	index;

	index = start;
	if (j)
	{
		while (s[index])
		{
			if (s[index] == c)
				return (index);
			index++;
		}
	}
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	space_afterpipe(char *str, int i)
{
	int		j;

	if (i)
	{
		j = ft_strlen(str) - 1;
		if (str[0] == '|' || str[j] == '|')
		{
			error('|');
			return (0);
		}
		return (1);
	}
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '|')
		return (0);
	return (1);
}

int	check_pipes(char *str)
{
	int		len;
	int		i;
	char	p;

	len = ft_strlen(str) - 1;
	if (str[len] == '|')
		return (error('|'));
	i = -1;
	p = '|';
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = check_pairs(str, str[i], i + 1, 1);
		if (str[i] == p && (str[i + 1] == p))
			return (error(str[i]));
		if (str[i] == p && ((str[i + 1] == p || !ft_strchar("<>", str[i - 1])) \
			|| !ft_strchar("<>", str[i - 1]) \
				&& !space_afterpipe(&str[i + 1], 0)))
			return (error(str[i - 1]));
		if ((str[i] == p && !space_afterpipe(&str[i + 1], 0)))
			return (error(str[i]));
	}
	return (1);
}

int	is_valide(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = -1;
	s = ft_strtrim(str, " \t");
	if (!*s)
		return (0);
	while (s[++i])
	{
		j = i;
		if (s[i] == '\'' || s[i] == '\"')
			i = check_pairs(s, s[i], i + 1, 0);
		if (i == -1)
			return (error(s[j]));
	}
	if (!space_afterpipe(s, 1) || !check_pipes(s) || \
		!check_ampersand(s) || !check_redirections(s))
		return (0);
	return (1);
}

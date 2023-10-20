/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isValide.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:46:07 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/18 16:07:05 by kzerri           ###   ########.fr       */
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

int	space_afterpipe(char *str)
{
	while (*str == ' ' && str++)
		;
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
	if (str[0] == '|' || str[len] == '|')
		return (error('|'));
	i = -1;
	p = '|';
	while (str[++i])
	{
		if (ft_strchar("\'\"", str[i]))
		{
			while (str[i + 1] && str[i + 1] != '\'' && str[i + 1] != '\"')
				i++;
		}
		if (str[i] == p && (str[i + 1] == p || !ft_strchar("<>", str[i - 1])))
			return (error(str[i]));
		if (str[i] == p && !space_afterpipe(&str[i + 1]))
			return (error(str[i]));
	}
	return (1);
}

int	check_pairs(char *s, char c, int start)
{
	int	index;

	index = start;
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	is_valide(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = i;
		if (str[i] == '\'' || str[i] == '\"')
			i = check_pairs(str, str[i], i + 1);
		if (i == -1)
			return (error(str[j]));
	}
	if (!check_pipes(str) || !check_ampersand(str) || !check_redirections(str))
		return (0);
	return (1);
}

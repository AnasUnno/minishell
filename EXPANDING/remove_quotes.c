/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:37:50 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/17 12:36:26 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rmv(char *str, char *s, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		*s++ = str[i];
		i++;
	}
	return (i);
}

char	*remove_quotes(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	s = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		j = ft_strlen(s);
		if (str[i] == '\'')
			i = rmv(str, &s[j], i + 1, str[i]);
		else if (str[i] == '\"')
			i = rmv(str, &s[j], i + 1, str[i]);
		else
			s[j] = str[i];
		i++;
	}
	return (s);
}

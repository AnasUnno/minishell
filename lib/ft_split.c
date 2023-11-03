/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:54:42 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 23:44:20 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**ft_free(char **p, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(p[i]);
		p[i] = NULL;
		i++;
	}
	free(p);
	return (NULL);
}

static	int	letters_c(char const *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != c && s1[i])
		i++;
	return (i);
}

static	char	**init_w(char const *s1, char c)
{
	int		j;
	char	**s2;

	j = 0;
	s2 = NULL;
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1 == '\0')
			break ;
		while (*s1 != c && *s1)
			s1++;
		j += 1;
	}
	if (j > 0)
		s2 = (char **)ft_malloc(sizeof(char *) * (j + 1));
	if (!s2)
		return (NULL);
	s2[j] = NULL;
	return (s2);
}

static	char	**ft_set(char const *s1, char c)
{
	int		j;
	char	**p;

	j = 0;
	if (!s1)
		return (NULL);
	p = init_w(s1, c);
	if (!p)
		return (NULL);
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1 == '\0')
			break ;
		p[j] = (char *)ft_malloc(sizeof(char) * (letters_c(s1, c) + 1));
		if (!p[j])
			return (ft_free(p, j));
		while (*s1 != c && *s1)
			s1++;
		j++;
	}
	return (p);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		j;
	int		k;

	j = 0;
	p = ft_set(s, c);
	if (!p)
		return (NULL);
	while (*s)
	{
		k = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			p[j][k] = *s;
			s++;
			k++;
		}
		if (p[j] != 0)
			p[j][k] = '\0';
		j++;
	}
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:01:24 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/02 11:02:30 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*p;
	size_t	j;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	j = 0;
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	while (j < i)
	{
		*(p + j) = *(s1 + j);
		j++;
	}
	*(p + j) = '\0';
	return (p);
}

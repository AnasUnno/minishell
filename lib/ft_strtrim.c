/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:50:47 by kzerri            #+#    #+#             */
/*   Updated: 2023/09/25 18:16:57 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t			start;
	size_t			end;
	char			*new;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	end = ft_strlen(s1);
	if (set == NULL)
		return ((char *)s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, (s1[end - 1])) && end - start > 0)
		end--;
	new = (char *)malloc(sizeof (char) * (end - start + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s1[start], end - start + 1);
	return (new);
}

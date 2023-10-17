/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:44:34 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/17 14:43:54 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_data	*ft_mylstnew(char *content, char *content2)
{
	t_data	*new;

	new = malloc(sizeof (t_data));
	if (!new)
		return (NULL);
	new->variable = content;
	new->value = content2;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*ptr;

	ptr = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_lstlast(*(lst));
		ptr->next = new;
	}
}

t_data	*ft_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst ->next;
	}
	return (lst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char const		*subs;	
	char			*a;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		subs = malloc((sizeof (char) * (ft_strlen(s) - start + 1)));
	else
		subs = malloc((sizeof (char) * (len + 1)));
	if (!subs)
		return (NULL);
	i = 0;
	a = (char *)subs;
	while (len-- && s[start])
		a[i++] = s[start++];
	a[i] = '\0';
	return ((char *)subs);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

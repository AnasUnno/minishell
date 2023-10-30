/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:02:25 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 00:47:17 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	if (!s1 || !s2)
		return (1);
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((ps1[i] == ps2[i]) && (ps1[i] || ps1[i]) && i < n - 1)
		i++;
	if ((ps1[i] - ps2[i]) == 0)
		return (0);
	else if ((ps1[i] - ps2[i]) > 0)
		return (1);
	return (1);
}

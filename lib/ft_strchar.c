/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:51:59 by kzerri            #+#    #+#             */
/*   Updated: 2023/09/25 18:14:36 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchar(char *str, char c)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == c)
			return (0);
		str++;
	}
	return (1);
}

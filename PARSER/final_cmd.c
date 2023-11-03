/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:22:27 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 00:22:55 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*final_str(char *str)
{
	char	*final;
	char	*operators;
	int		index;
	int		size;
	char	*tmp;

	tmp = ft_strtrim(str, " \t\n");
	free(str);
	str = NULL;
	str = tmp;
	size = ft_strlen(tmp);
	operators = "<|>";
	final = ft_calloc((size * 2) + 1, 1);
	index = 0;
	if (!final)
		return (NULL);
	while (*tmp && index < size * 2)
		fill_final(&final, &tmp, &index, operators);
	return (free(str), final);
}

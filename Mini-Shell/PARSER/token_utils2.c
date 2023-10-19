/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:06:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/26 15:53:41 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	helper3(char *str, int *in_quote, int *i, char *c)
{
	*in_quote = 1;
	*c = str[*i];
	(*i)++;
}

void	helper4(int *in_quote, int *i, char *c)
{
	*in_quote = 0;
	*c = 0;
	(*i)++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:44:38 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:42 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    first_on(t_data **tmp, t_data **environement)
{
    *environement = (*environement)->next;
	free((*tmp)->variable);
	free((*tmp)->value);
	free(*tmp);
	tmp = NULL;
}

void    last_on(t_data **tmp2, t_data **tmp, t_data **environement)
{
    *tmp2 = get_before(*environement, *tmp);
	(*tmp2)->next = NULL;
	free((*tmp)->variable);
	free((*tmp)->value);
	free(*tmp);
	tmp = NULL;
}

void    in_middle(t_data **tmp2, t_data **tmp, t_data **environement)
{
    *tmp2 = get_before(*environement, *tmp);
	(*tmp2)->next = (*tmp)->next;
	free((*tmp)->variable);
	free((*tmp)->value);
	free(*tmp);
	tmp = NULL;
}
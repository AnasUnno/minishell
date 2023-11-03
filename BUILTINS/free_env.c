/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:33:08 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/03 02:17:30 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_exp(t_export *exp)
{
	exp->i = 0;
	exp->status = 0;
	exp->str = NULL;
}

void	free_env(t_data **env)
{
	t_data	*tmp;

	while (*env)
	{
		tmp = *env;
		if (!tmp)
			return ;
		*env = (*env)->next;
		if (tmp && tmp->variable)
			free(tmp->variable);
		if (tmp && tmp->value)
			free(tmp);
	}
	*env = NULL;
	tmp = NULL;
}

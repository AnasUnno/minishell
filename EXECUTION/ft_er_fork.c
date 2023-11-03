/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_er_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:59:12 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 16:39:34 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_er_fork(void)
{
	ft_printf("fork : Failed");
	exit(1);
}

void	end_exec(char *s, char **args)
{
	ft_printf("Minishell: %s: command not found !\n", s);
	free_all(args);
}

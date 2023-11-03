/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:42:24 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/01 23:45:19 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = getenv("PWD");
		printf("%s\n", path);
		return (0);
	}
	else if (path)
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
	return (1);
}

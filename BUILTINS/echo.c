/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:55:02 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/17 17:58:50 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	check_full_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
		{
			i++;
			if (str[i] == '\0')
				return (1);
		}
		return (0);
	}
	return (0);
}

int	echo(char **av)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 0;
	while (av[i])
	{
		if (check_full_n(av[i]))
		{
			new_line = 1;
			i++;
		}
		else
		{
			while (av[i])
			{
				printf("%s", av[i++]);
				if (av[i])
					printf(" ");
			}
		}
	}
	if (!new_line)
		printf("\n");
	return (0);
}

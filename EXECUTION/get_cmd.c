/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:55:36 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/07 13:36:48 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_args(char *s, char **args, t_data *env)
{
	int	i;

	i = -1;
	while (env)
	{
		if (!ft_strncmp(env->variable, "PATH", 4))
		{
			args = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (!env)
		return (free_all(args), NULL);
	while (args && args[++i])
	{
		args[i] = ft_strjoin(args[i], "/");
		args[i] = ft_strjoin(args[i], s);
	}
	return (args);
}

char	*get_cmd(char *s, t_data *env)
{
	char	**args;
	int		i;

	args = NULL;
	if (s && *s)
	{
		args = get_args(s, args, env);
		i = -1;
		while (args && args[++i])
		{
			if (!access(args[i], F_OK | X_OK))
			{
				free(s);
				s = ft_strdup(args[i]);
				return (free_all(args), s);
			}
		}
	}
	else
	{
		free(s);
		s = ft_strdup("");
	}
	end_exec(s, args);
	exit(127);
}

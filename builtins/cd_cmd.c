/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:56:24 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/12 17:54:14 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_old_pwd(char *path, t_data **envi)
{
	t_data	*tmp;

	if (ft_strcmp(path, "-"))
	{
		ft_printf("Minishell: cd: -%s: invalid option\n", path);
		return (1);
	}
	else
	{
		tmp = get_variable(*envi, "OLDPWD");
		if (tmp->value)
			chdir(tmp->value);
		else
		{
			ft_printf("Minishell: cd: OLDPWD not set\n");
			return (1);
		}
	}
	return (0);
}

int	cd_home(char *path, t_data **envi)
{
	t_data	*tmp;
	
	tmp = get_variable(*envi, "HOME");
	if (!path)
	{
		if (!tmp->value)
			ft_printf("Minishell: cd: HOME not set\n");
		else
		{
			chdir(tmp->value);
			return (0);
		}
	}
	return (1);
}

int	cd_home2(char *path, t_data **envi)
{
	t_data	*tmp;
	
	if (ft_strcmp(path, "~"))
		ft_printf("Minishell: cd: %s: No such file or directory\n", path);
	else
	{
		tmp = get_variable(*envi, "HOME");
		if (!tmp->value)
			ft_printf("Minishell: cd: HOME not set\n");
		else
		{
			chdir(tmp->value);
			return (0);
		}
	}
	return (1);
}

void	update_pwd(char *path, t_data **tmp, t_data **tmp2, char *str)
{
	if (path[0] == '-')
	{
		(*tmp2)->value = (*tmp)->value;
		(*tmp)->value = str;
	}
	else
	{
		str = (*tmp)->value;
		if ((*tmp)->value)
			free((*tmp)->value);
		(*tmp)->value = getcwd(NULL, 0);
		if ((*tmp2)->value)
			free((*tmp2)->value);
		(*tmp2)->value = str;
	}
}

int	cd(char *path, t_data **envi)
{
	int		r_type;
	t_data	*tmp;
	t_data	*tmp2;
	char	*str;

	r_type = 0;
	tmp = get_variable(*envi, "PWD");
	tmp2 = get_variable(*envi, "OLDPWD");
	str = tmp2->value;
	if (!path)
		r_type = cd_home(path, envi);
	else if (path[0] == '-')
		r_type = cd_old_pwd(path, envi);
	else if (path[0] == '~')
		r_type = cd_home2(path, envi);
	else
		r_type = chdir(path);
	if (!r_type)
		update_pwd(path, &tmp, &tmp2, str);
	return (r_type);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:56:24 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/03 17:03:24 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_old_pwd(char *path, t_data **envi)
{
	t_data	*tmp;

	if (my_strcmp(path, "-"))
	{
		ft_printf("Minishell: cd: -%s: invalid option\n", path);
		return (1);
	}
	else
	{
		tmp = get_variable(*envi, "OLDPWD");
		if (tmp && tmp->value)
		{
			if (chdir(tmp->value) == -1)
			{
				ft_printf("minishell: cd: %s: No such file or directory\n",
					tmp->value);
				return (1);
			}
			else
				pwd();
		}
		else
			return (ft_printf("Minishell: cd: OLDPWD not set\n"), 1);
	}
	return (0);
}

int	cd_home(char *path, t_data **envi, int flag)
{
	t_data	*tmp;

	if (flag == 1)
	{
		if (chdir(path) != -1)
			return (0);
		return (ft_printf("minishell: cd: %s: No such file or directory\n",
				path), 1);
	}
	else
	{
		tmp = get_variable(*envi, "HOME");
		if (!tmp || !tmp->value)
			ft_printf("Minishell: cd: HOME not set\n");
		else
		{
			if (chdir(tmp->value) == -1)
				return (ft_printf("minishell: cd: %s: No such file or \
					directory\n", tmp->value), 1);
			return (0);
		}
	}
	return (1);
}

int	cd_home2(char *path, t_data **envi)
{
	t_data	*tmp;

	if (my_strcmp(path, "~"))
		ft_printf("Minishell: cd: %s: No such file or directory\n", path);
	else
	{
		tmp = get_variable(*envi, "HOME");
		if (!tmp || !tmp->value)
			ft_printf("Minishell: cd: HOME not set\n");
		else
		{
			if (chdir(tmp->value) == -1)
			{
				ft_printf("minishell: cd: %s: No such file or directory\n",
					tmp->value);
				return (1);
			}
			return (0);
		}
	}
	return (1);
}

void	update_pwd(t_data **env, t_cd var, t_data **pwd, t_data **old)
{
	if (!pwd || !*pwd)
	{
		*pwd = ft_mylstnew(ft_strdup("PWD"), getcwd(NULL, 0));
		ft_lstadd_back(env, *pwd);
	}
	else
	{
		free((*pwd)->value);
		(*pwd)->value = getcwd(NULL, 0);
	}
	if (!old || !*old)
	{
		*old = ft_mylstnew(ft_strdup("OLDPWD"), ft_strdup(var.tmp));
		ft_lstadd_back(env, *old);
	}
	else
	{
		free((*old)->value);
		(*old)->value = ft_strdup(var.tmp);
	}
}

int	cd(char *pathe, t_data **envi)
{
	t_data	*old;
	t_data	*pwd;
	t_cd	var;

	var.r_type = 0;
	if (envi && *envi)
		(*envi)->path = pathe;
	var.tmp = getcwd(NULL, 0);
	pwd = get_variable(*envi, "PWD");
	old = get_variable(*envi, "OLDPWD");
	if (old)
		var.str = old->value;
	if (!pathe)
		var.r_type = cd_home(pathe, envi, 0);
	else if (pathe[0] == '-')
		var.r_type = cd_old_pwd(pathe, envi);
	else if (pathe[0] == '~')
		var.r_type = cd_home2(pathe, envi);
	else
		var.r_type = cd_home(pathe, envi, 1);
	if (!var.r_type)
		update_pwd(envi, var, &pwd, &old);
	else if (var.r_type == -1)
		return (free(var.tmp), 1);
	return (free(var.tmp), var.r_type);
}

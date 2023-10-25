/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:56:24 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/20 14:17:01 by kzerri           ###   ########.fr       */
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
		if (chdir(path) == -1)
			return (ft_printf("minishell: cd: %s: No such file or directory\n", 
					path), 1);
	}
	else
	{
		tmp = get_variable(*envi, "HOME");
		if (!tmp->value)
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

int	cd_home2(char *path, t_data **envi)
{
	t_data	*tmp;

	if (my_strcmp(path, "~"))
		ft_printf("Minishell: cd: %s: No such file or directory\n", path);
	else
	{
		tmp = get_variable(*envi, "HOME");
		if (!tmp->value)
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

void	update_pwd(t_data **env, t_data **tmp, t_data **tmp2, char *str)
{
	if ((*env)->path && (*env)->path[0] == '-')
	{
		(*tmp2)->value = (*tmp)->value;
		(*tmp)->value = str;
	}
	else
	{
		str = (*tmp)->value;
		(*tmp)->value = getcwd(NULL, 0);
		if (tmp2 && *tmp2 && (*tmp2)->value)
		{
			free((*tmp2)->value);
			(*tmp2)->value = NULL;
		}
		if (!*tmp2)
		{
			*tmp2 = ft_mylstnew("OLDPWD", str);
			ft_lstadd_back(env, *tmp2);
		}
		else
			(*tmp2)->value = str;
		str = NULL;
	}
}

int	cd(char *pathe, t_data **envi)
{
	int		r_type;
	t_data	*tmp;
	t_data	*tmp2;
	char	*str;

	r_type = 0;
	(*envi)->path = pathe;
	tmp = get_variable(*envi, "PWD");
	tmp2 = get_variable(*envi, "OLDPWD");
	if (tmp2)
		str = tmp2->value;
	if (!pathe)
		r_type = cd_home(pathe, envi, 0);
	else if (pathe[0] == '-')
		r_type = cd_old_pwd(pathe, envi);
	else if (pathe[0] == '~')
		r_type = cd_home2(pathe, envi);
	else
		r_type = cd_home(pathe, envi, 1);
	if (!r_type)
		update_pwd(envi, &tmp, &tmp2, str);
	else if (r_type == -1)
		return (1);
	return (r_type);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_double_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:11 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/04 13:24:25 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*random_file(char *s, int i, char *herdoc)
{
	DIR				*dir;
	struct dirent	*entry_point;
	char			*str;
	char			*n;

	str = ft_strdup(s);
	n = ft_itoa(i);
	dir = opendir("/tmp");
	if (!dir)
	{
		ft_printf("Directory you trying to open doesn\'t exist !\n");
		return (NULL);
	}
	entry_point = readdir(dir);
	while (entry_point)
	{
		if (!ft_strncmp(entry_point->d_name, herdoc, 6))
		{
			str = ft_strjoin(str, n);
			return (closedir(dir), free(n), str);
		}
		entry_point = readdir(dir);
	}
	return (closedir(dir), free(n), str);
}

void	signale_handler(int num)
{
	int	fds[2];

	(void)num;
	pipe(fds);
	rl_replace_line("", 0);
	dup2(fds[0], STDIN_FILENO);
	write(fds[1], "\n", 1);
	close(fds[0]); 
	close(fds[1]);
	g_status = -1;
}

int	check_signal(t_vars *var)
{
	var->backup_fd = dup(STDIN_FILENO);
	if (g_status == -1)
	{
		free_vars(var);
		dup2(var->backup_fd, STDIN_FILENO);
		close(var->backup_fd);
		return (1);
	}
	close(var->backup_fd);
	return (0);
}

void	ft_l_double_red(t_tree *tree, t_data *envi)
{
	t_vars		var;
	static int	i;

	var.s = random_file("/tmp/HERDOC", ++i, "HERDOC");
	var.fd = open(var.s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	var.del = remove_quotes_h(tree->right->strs[0], &var.i);
	while (1)
	{
		signal(SIGINT, signale_handler);
		if (check_signal(&var))
			return ;
		var.str = readline("> ");
		if (!var.str || ft_strcmp(var.str, var.del))
			break ;
		if (!var.i)
			var.str = clean_str_h(var.str, envi);
		ft_putstr_fd(var.str, var.fd);
		ft_putstr_fd("\n", var.fd);
		free(var.str);
	}
	free(tree->right->strs[0]);
	tree->right->strs[0] = ft_strdup(var.s);
	free_vars(&var);
	free(var.str);
}

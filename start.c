/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:22:50 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/19 12:01:38 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd(char c)
{
	if (c!= ' '&& c != '>' && c != '<' && c != '|')
		return (1);
	return (0);
}


static void	creat_cmd(t_list **cmd, char *str, size_t start, size_t len)
{
	t_list	*cmd2;
	char	*string;
	static	int	flag;

	string = ft_substr(str, start, len);

	if (!flag)
	{
		*cmd = ft_lstnew(string);
		flag = 1;
	}
	else
	{
		cmd2 = ft_lstnew(string);
		ft_lstadd_back(cmd, cmd2);
	}
}

// static int	wich_op(char *str, int i)
// {
// 	if (str[i] == '|')
// 		return (0);
// 	else if (str[i] == '>')
// 	{
// 		if (str[i + 1] == '>')
// 			return (1);
// 	}
// 	else if (str[i] == '<')
// 	{
// 		if (str[i + 1] == '<')
// 			return (2);
// 	}
// }

static t_list	*get_cmd(char *str)
{
	int		i;
	size_t	start;
	size_t	len;
	t_list	*cmd;

	i = 0;
	len = 0;
	cmd = NULL;
	while(str[i])
	{
		start = i;
		while (str[i] && is_cmd(str[i]))
		{
			i++;
			len++;
		}
		creat_cmd(&cmd, str, start, len);
		len = 0;
		while (str[i] && is_cmd(str[i]) == 0)
		{
			i++;
		}
	}
	return (cmd);
}

char	*get_str_ready(char *str)
{
	int			i;
	char	*str1;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	str1 = ft_strtrim(str, " ");
	free(str);
	str = NULL;
	while (str1[i])
	{
		if (is_cmd(str1[i]))
			flag = 1;
		else if (str1[i] == ' ' && flag)
		{
			count++;
			flag = 0;
		}
		i++;
	}	
}

int main()
{
	char *str = readline("$Minishell: ");
	t_list *cmd = get_cmd(str);
	while(cmd)
	{
	 	printf("|%s|\n", cmd->content);
		cmd = cmd->next;
	}
	
}
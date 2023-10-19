/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:05:06 by kzerri            #+#    #+#             */
/*   Updated: 2023/09/23 18:57:50 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countRedirections(char *str, int *i)
{
	int j;

	j = 1;
	while (str[*i])
	{
		if ()		
	}	
}

int checkRedirections(char *str)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(str) - 1;
	if (!ft_strchr("<>", str[len]))
		return (0);
	while (!ft_strchr("<>", str[++i]));
	if (!str[i])
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("<>", str[i]))
		{
			i++;
			if (!countRedirections(&str[i], &i));
				return (0);
		}
	}
	return (1);
}

int	checkAmpersand(char *str)
{
	while (*str)
	{
		if (*str == '&')
			return (0);
		str++;
	}
	return (1);
}
int	spaceAfterPipe(char *str)
{
	while (*str == ' ' && str++);
	if (*str == '|')
		return (0);
	return (1);
}

int	checkPipes(char *str)
{
	int		len;
	int		i;
	char	p;

	len = ft_strlen(str) - 1;
	if (str[0] == '|')
		return (0);
	i = -1;
	p = '|';
	while (str[++i])
	{
		if (str[i] == p && str[i + 1] == p)
			return (0);
		if (str[i] == '|' && !spaceAfterPipe(&str[i + 1]))
			return (0);
	}
	return (1);
}
int	check_pairs(char *s, char c, int start)
{
	int index;

	index = start;
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	isValide(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = check_pairs(str, str[i], i + 1);
		if (i == -1)
			return (0);
	}
	if (!checkPipes(str) || !checkAmpersand(str))
		return (0);
	return (1);
}

int main(int ac, char **av, char **env)
{
	char *string = "\"ls -la |\' 'wc -l'\" | \"ls\"\'\'s\'\'";
	// printf("%s\n", string);
	if (isValide(string))
		printf("Is valide\n");
	else
		printf("minishell: syntax error near unexpected token `|'\n");
	// int len;
	// char *str;  

	// if (ac > 1)
	// {
	// 	str = NULL;
	// 	len = count_params(av);
	// 	str = get_line(av, str, len);
	// }
	// printf("%s\n", str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:37:50 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 17:42:50 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rmv(char *str, char *s, int i, char c)
{
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		*s++ = str[i];
		i++;
	}
	return (i);
}

char	*remove_quotes(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	s = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		j = ft_strlen(s);
		if (str[i] == '\'')
			i = rmv(str, &s[j], i + 1, str[i]);
		else if (str[i] == '\"')
			i = rmv(str, &s[j], i + 1, str[i]);
		else
			s[j] = str[i];
		i++;
	}
	return (free(str), s);
}

char	*remove_quotes_h(char *str, int *x)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	*x = 0;
	j = 0;
	s = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i] && str[i] != '\'' && str[i] != '\"')
		i++;
	if (str[i] == '\'' || str[i] == '\"')
		*x = 1;
	i = 0;
	while (str[i])
	{
		j = ft_strlen(s);
		if (str[i] == '\'')
			i = rmv(str, &s[j], i + 1, str[i]);
		else if (str[i] == '\"')
			i = rmv(str, &s[j], i + 1, str[i]);
		else
			s[j] = str[i];
		i++;
	}
	return (s);
}

char	*clean_str_h(char *str, t_data *envi)
{
	t_var	var;

	var.i = 0;
	var.y = allocation(str, envi);
	var.s = (char *)ft_calloc(var.y + 1, 1);
	var.j = 0;
	var.fr = NULL;
	while (str[var.i])
	{
		if (str[var.i] == '$')
		{
			free(var.fr);
			var.tmp = get_var_value(str, &var.i, envi);
			var.fr = var.tmp;
			while (*var.tmp)
				var.s[var.j++] = *var.tmp++;
			continue ;
		}
		var.s[var.j++] = str[var.i];
		var.i++;
	}
	return (free(str), free(var.fr), var.s);
}

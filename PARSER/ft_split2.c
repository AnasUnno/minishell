/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:15:38 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/29 21:52:30 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_word_helper(char **str, int *in_quote, char *c, int *count)
{
	char	*white_spaces;

	white_spaces = " \t\n";
	if ((**str == '\'' || **str == '\"') && !*in_quote)
	{
		*in_quote = 1;
		*c = *(*str)++;
	}
	else if (*(*str) == *c && *in_quote)
	{
		*in_quote = 0;
		*c = 0;
		(*str)++;
	}
	else if (ft_strchr(white_spaces, *(*str)) && !*in_quote)
	{
		while (ft_strchr(white_spaces, *(*str)))
			(*str)++;
		(*count)++;
	}
	else
		(*str)++;
}

static void	helper3(char *str, int *in_quote, int *i, char *c)
{
	*in_quote = 1;
	*c = str[*i];
	(*i)++;
}

static void	helper4(int *in_quote, int *i, char *c)
{
	*in_quote = 0;
	*c = 0;
	(*i)++;
}

static int	count_words(char *str)
{
	int		count;
	int		in_quote;
	char	c;

	count = 0;
	in_quote = 0;
	while (*str)
		count_word_helper(&str, &in_quote, &c, &count);
	if (!in_quote)
		count++;
	return (count);
}

char	**ft_split2(char *str)
{
	t_vars	var;

	var.white_spaces = " \t\n";
	helper(&var.in_quote, &var.i, &var.j, &var.start);
	var.trimmed = ft_strtrim(str, " \t");
	var.count = count_words(var.trimmed);
	var.splited = (char **)malloc(sizeof(char *) * (var.count + 1));
	while (var.trimmed[var.i])
	{
		if ((var.trimmed[var.i] == '\'' || var.trimmed[var.i] == '\"') && !var.in_quote)
			helper3(var.trimmed, &var.in_quote, &var.i, &var.c);
		else if (var.trimmed[var.i] == var.c && var.in_quote)
			helper4(&var.in_quote, &var.i, &var.c);
		else if (ft_strchr(var.white_spaces, var.trimmed[var.i]) && !var.in_quote)
			var.splited[var.j++] = helper2(var.trimmed, &var.i, &var.start);
		else
			var.i++;
	}
	if (!var.in_quote)
	{
		var.splited[var.j] = (char *)malloc(sizeof(char) \
			* ((var.i - var.start) + 1));
		ft_strncpy(var.splited[var.j++], &var.trimmed[var.start], var.i - var.start);
	}
	return (var.splited[var.j] = NULL, free(str), free(var.trimmed), var.splited);
}

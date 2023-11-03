/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:15:38 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/02 23:44:20 by kzerri           ###   ########.fr       */
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
	helper(&var.iq, &var.i, &var.j, &var.st);
	var.tr = ft_strtrim(str, " \t");
	var.count = count_words(var.tr);
	var.splited = (char **)ft_malloc(sizeof(char *) * (var.count + 1));
	while (var.tr[var.i])
	{
		if ((var.tr[var.i] == '\'' || var.tr[var.i] == '\"') && !var.iq)
			helper3(var.tr, &var.iq, &var.i, &var.c);
		else if (var.tr[var.i] == var.c && var.iq)
			helper4(&var.iq, &var.i, &var.c);
		else if (ft_strchr(var.white_spaces, var.tr[var.i]) && !var.iq)
			var.splited[var.j++] = helper2(var.tr, &var.i, &var.st);
		else
			var.i++;
	}
	if (!var.iq)
	{
		var.splited[var.j] = (char *)ft_malloc(sizeof(char) \
			* ((var.i - var.st) + 1));
		ft_strncpy(var.splited[var.j++], &var.tr[var.st], var.i - var.st);
	}
	return (var.splited[var.j] = NULL, free(str), free(var.tr), var.splited);
}

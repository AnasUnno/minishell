/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/25 18:19:23 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*final_str(char *str)
{
	char	*final;
	char	*operators;
	int		index;
	int		size;
	char	*tmp;

	tmp = ft_strtrim(str, " ");
	free(str);
	str = NULL;
	size = ft_strlen(tmp);
	operators = "<|>";
	final = ft_calloc((size * 2) + 1, 1);
	index = 0;
	if (!final)
		return (NULL);
	while (*tmp && index < size * 2)
	{
		if (!ft_strchr(operators, *tmp))
			final[index++] = *tmp++;
		else
			process_operator(&final, &tmp, &index);
	}
	return (final);
}

int	count_words(char *str)
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

	helper(&var.in_quote, &var.i, &var.j, &var.start);
	var.count = count_words(str);
	var.splited = (char **)malloc(sizeof(char *) * (var.count + 1));
	while (str[var.i])
	{
		if ((str[var.i] == '\'' || str[var.i] == '\"') && !var.in_quote)
			helper3(str, &var.in_quote, &var.i, &var.c);
		else if (str[var.i] == var.c && var.in_quote)
			helper4(&var.in_quote, &var.i, &var.c);
		else if (str[var.i] == ' ' && !var.in_quote)
			var.splited[var.j++] = helper2(str, &var.i, &var.start);
		else
			var.i++;
	}
	if (!var.in_quote)
	{
		var.splited[var.j] = (char *)malloc(sizeof(char) \
			* ((var.i - var.start) + 1));
		ft_strncpy(var.splited[var.j++], &str[var.start], var.i - var.start);
	}
	return (var.splited[var.j] = NULL, var.splited);
}

// int main(void)
// {
// 	char *str0 = readline("$Minishell : ");
// 	char *final = final_str(str0);
// 	char **splited = ft_split2(final);
// 	printf("%s\n", final);
// 	printf(" number of words is : %d\n", count_words(final));
// 	int i = 0;
// 	int	j;
// 	while (splited[i]){
// 		j = 0;
// 		printf("%s\n", splited[i]);
// 		i++;
// 	}
// }
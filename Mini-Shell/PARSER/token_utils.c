/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:29:26 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/09 15:40:00 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_operator(char **final, char **str, int *index)
{
	char	c;

	c = *(*str);
	(*final)[(*index)++] = ' ';
	(*final)[(*index)++] = *(*str);
	if (*(*str) == '<' || *(*str) == '>')
	{
		if (*((*str) + 1) == c)
		{
			(*final)[(*index)++] = *((*str) + 1);
			(*str)++;
		}
	}
	(*final)[(*index)++] = ' ';
	(*str)++;
}

void	count_word_helper(char **str, int *in_quote, char *c, int *count)
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

void	helper(int *in_quote, int *i, int *j, int *start)
{
	*in_quote = 0;
	*i = 0;
	*j = 0;
	*start = 0;
}

char	*helper2(char *str, int *i, int *start)
{
	char	*word;
	char	*white_space;
	int		j;

	j = *i;
	white_space = " \t\n";
	while (str[j] && ft_strchr(white_space, str[j]))
		j++;
	word = (char *)malloc(sizeof(char) * (*i - *start + 1));
	if (word != NULL)
	{
		ft_strncpy(word, &str[*start], *i - *start);
		*i = j;
		*start = *i;
	}
	return (word);
}

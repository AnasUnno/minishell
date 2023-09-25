/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:51:18 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/24 20:16:45 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (*(*str) == ' ' && !*in_quote)
	{
		while (*(*str) == ' ')
			(*str)++;
		(*count)++;
	}
	else
		(*str)++;
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
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

	while (str[*i] == ' ')
		(*i)++;
	word = (char *)malloc(sizeof(char) * (*i - *start + 1));
	if (word != NULL)
	{
		ft_strncpy(word, &str[*start], *i - *start);
		*start = *i;
	}
	return (word);
}

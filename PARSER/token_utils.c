/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:29:26 by kzerri            #+#    #+#             */
/*   Updated: 2023/11/04 13:24:07 by kzerri           ###   ########.fr       */
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

void	fill_final(char **final, char **tmp, int *index, char *operators)
{
	char	c;

	c = 0;
	if (ft_strchr("'\'\"", *(*tmp)))
	{
		c = *(*tmp);
		(*final)[(*index)++] = *(*tmp)++;
		while (*tmp && *(*tmp) != c)
			(*final)[(*index)++] = *(*tmp)++;
		(*final)[(*index)++] = *(*tmp)++;
	}
	else if (ft_strchr(operators, *(*tmp)))
	{
		if (*(*tmp) == '>' || *(*tmp) == '<')
			process_operator(final, tmp, index);
		else
		{
			(*final)[(*index)++] = ' ';
			(*final)[(*index)++] = *(*tmp)++;
			(*final)[(*index)++] = ' ';
		}
	}
	else
		(*final)[(*index)++] = *(*tmp)++;
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
	word = (char *)ft_malloc(sizeof(char) * (*i - *start + 1));
	if (!word)
		return (NULL);
	if (word != NULL)
	{
		ft_strncpy(word, &str[*start], *i - *start);
		*i = j;
		*start = *i;
	}
	return (word);
}

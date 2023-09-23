/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:07:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/23 14:01:23 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_str_ready(char *str)
{
    int size;
    char *new;
    int i;
    int flag;
    int j;

    size = count_str(str);
    new = malloc(sizeof(char) * (size + 1));
    if (!new)
        return (0);
    i = 0;
    flag = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
        {
            new[j++] = str[i];
            flag = 1;
        }
        else if (str[i] == ' ' && flag)
        {
            new[j++] = ' ';
            flag = 0;
        }
        i++;
    }
    new[j] = '\0';
    return (new);
}

char	*final_str(char *str)
{
	int		i;
	char	*final;
	char	*operators = ">|<";
	int		index;
	char	c;
	int size;

	size = ft_strlen(str);
	index = 0;
	final = ft_calloc((size * 2) + 1, 1);
	if (!final)
		return (NULL);
	i = 0;
	while (str[i] && index < size * 2)
	{
		if (!ft_strchr(operators, str[i]))
			final[index++] = str[i++];
		else
		{
			final[index++] = ' ';
			final[index++] = str[i];
			if (str[i] == '<' || str[i] == '>')
			{
				c = str[i];
				if (str[i + 1] == c)
				{
					final[index++] = str[i + 1];
					i++;
				}
			}
			final[index++] = ' ';
			i++;
		}
	}
	return (final);
}

int count_words(const char *str)
{
    int count = 0;
    int i = 0;
    bool in_quote = false;
    char c;

    while (str[i])
	{
        if ((str[i] == '\'' || str[i] == '\"') && !in_quote)
		{
            in_quote = true;
            c = str[i];
            i++;
        } 
		else if (str[i] == c && in_quote)
		{
            in_quote = false;
            c = 0;
            i++;
        } 
		else if (str[i] == ' ' && !in_quote)
		{
            while (str[i] == ' ') 
                i++;
            count++;
        }
		else
            i++;
    }
	if (!in_quote)
		count++;
    return count;
}

char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**ft_split2(char *str)
{
	int i = 0;
	int start = 0;
	int j = 0;
	int count = count_words(str);
	char	c;
	char **splited = (char **)malloc(sizeof(char *) * (count + 1));
	int in_quote = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !in_quote)
		{
            in_quote = 1;
            c = str[i];
            i++;
        } 
		else if (str[i] == c && in_quote)
		{
            in_quote = 0;
            c = 0;
            i++;
        } 
		else if (str[i] == ' ' && !in_quote)
		{
            while (str[i] == ' ') 
                i++;
			splited[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
			ft_strncpy(splited[j++], &str[start], i - start);
			start = i;
        }
		else
            i++;
	}
	if (!in_quote)
	{
		splited[j] = (char *)malloc(sizeof(char) * ((i - start) + 1));
		ft_strncpy(splited[j++], &str[start], i - start);
	}
	splited[j] = NULL;
	return (splited);
}

int main(void)
{
	char *str0 = readline("$Minishell : ");
	char *final = final_str(str0);
	char **splited = ft_split2(final);
	printf("%s\n", final);
	printf(" number of words is : %d\n", count_words(final));
	int i = 0;
	int	j;
	while (splited[i]){
		j = 0;
		printf("%s\n", splited[i]);
		i++;
	}
}
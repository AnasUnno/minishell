/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:23:06 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/25 15:18:37 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*get_str_ready(char *str);
char	*final_str(char *str);
int		count_words(char *str);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**ft_split2(char *str);
void	process_operator(char **final, char **str, int *index);
void	count_word_helper(char **str, int *in_quote, char *c, int *count);
char	*ft_strncpy(char *s1, char *s2, int n);
void	check_op(char **str, int *i, int *in_quote, char *c);
void	helper(int *in_quote, int *i, int *j, int *start);
char	*helper2(char *str, int *i, int *start);
void	helper3(char *str, int *in_quote, int *i, char *c);
void	helper4(int *in_quote, int *i, char *c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *b, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

typedef struct s_vars
{
	int		i;
	int		start;
	int		j;
	int		count;
	char	c;
	char	**splited;
	int		in_quote;
}t_vars;

#endif

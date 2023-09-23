/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:23:06 by araji-af          #+#    #+#             */
/*   Updated: 2023/09/23 13:59:16 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 #include <readline/readline.h>
#include <readline/history.h>

int		check_carac(char c);
void	helper(char c, int space_count, int count, int flag);
int		count_str(char *str);
char	*get_str_ready(char *str);
char	*final_str(char *str);
int		count_words(const char *str);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**ft_split2(char *str);

// typedef struct s_token
// {
// 	char	*str;
// 	int		type;
// 	int		expansion_flag;
// 	struct	s_list	*next;
	
// }t_token;
#endif
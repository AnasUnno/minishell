/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:11:56 by kzerri            #+#    #+#             */
/*   Updated: 2023/09/23 16:21:42 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>


typedef struct s_tree
{
    int data;
    struct s_tree *right;
    struct s_tree *left;
}t_tree;

int	ft_strlen(char *str);
int	ft_strchr(char *str, char c);

#endif
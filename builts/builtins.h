/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:04:42 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/13 15:10:21 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>

typedef struct s_data
{
	char			*variable;
	char			*value;
	struct s_data	*next;
}t_data;

typedef struct s_export
{
	t_data	*tmp;
	int		end;
	int		end1;
	char	*str;
}t_export;

int		cd(char *path, t_data **envi);
int		echo(char **av);
void	get_environement(char **env, t_data **environement);
void	reset_old_pwd(t_data **envi);
void	env(t_data *envi);
int		check_export_args(char *str);
int		get_var_lenght(char *str);
int		get_value_lenght(int end, char *str);
int		check_append_new(char *str);
void	create_new_var(t_export *exp, char *av, t_data **envi);
void	no_option_export(t_data *envi);
void	initialize_exp_variable(t_export *var, char *av, t_data *envi);
void	append_operation(t_export *exp, char *av, t_data **envi);
void	create_update(t_export *exp, char *av, t_data **envi);
void	export(char **av, t_data **envi);
int		pwd(void);
void	first_on(t_data **tmp, t_data **environement);
void	last_on(t_data **tmp2, t_data **tmp, t_data **environement);
void	in_middle(t_data **tmp2, t_data **tmp, t_data **environement);
int		check_unset_params(char *str);
t_data	*get_variable(t_data *envi, char *str);
int		check_pos(t_data *envi, t_data *tmp);
t_data	*get_before(t_data *envi, t_data *tmp);
void	unset(char **av, t_data **environement);
t_data	*ft_mylstnew(char *content, char *content2);
void	ft_lstadd_back(t_data **lst, t_data *new);
t_data	*ft_lstlast(t_data *lst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	update_pwd(char *path, t_data **tmp, t_data **tmp2, char *str);
int		ft_atoi(char *str);
int		ft_exit(char **av);
int		ft_isdigit(int c);
int		is_format(char half_form);
int		printf_helper(va_list args, char format_speci);
int		ft_printf(const char *format, ...);
int		hexa_lower(unsigned int nbr);
int		hexa_upper(unsigned int nbr);
int		unsigned_forme(unsigned int nbr);
int		print_pointer(uintptr_t n);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putstr(const char *str);

#endif
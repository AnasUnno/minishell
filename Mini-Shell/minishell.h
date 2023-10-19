/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:11:56 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/19 16:38:15 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>

int	g_status;

typedef struct s_tree
{
	char			**strs;
	struct s_tree	*right;
	struct s_tree	*left;
	int				count;
}t_tree;

typedef struct s_var
{
	char	*s;
	char	*tmp;
	int		j;
	int		i;
}t_var;

typedef struct s_data
{
	char			*variable;
	char			*value;
	char			*path;
	struct s_data	*next;
}t_data;

typedef struct s_export
{
	t_data	*tmp;
	int		end;
	int		end1;
	char	*str;
}t_export;

typedef struct s_vars
{
	int		i;
	int		start;
	int		j;
	int		count;
	char	c;
	char	**splited;
	int		in_quote;
	char	*white_spaces;
}t_vars;

int		ft_strlen(char *str);
int		ft_strchar(char *str, char c);
char	*ft_strchr(char *s, int c);
char	*ft_strtrim(char *s1, char *set);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
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
int		ft_strcmp(char *s1, char *s2);
char	*get_str_ready(char *str);
char	*final_str(char *str);
int		count_words(char *str);
void	free_all(char **args);
int		count_redirections(char *str, int start, char c);
int		check_redirections(char *str);
int		check_ampersand(char *str);
int		is_valide(char *str);
int		error(char c);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	**level3(char **strs, char **cmd, int start);
void	level2(t_tree **tree, char **strs, int start, char **cmd);
void	level1(t_tree **tree, char **strs, int start);
char	*ft_strdup(char *s1);
void	execute(t_tree *tree, t_data *env, char **environement);
void	cmd_execute(t_tree *tree, t_data *env, char **environement);
char	*get_cmd(char *s, t_data *env);
void	ft_right_red(t_tree *tree, t_data *envi, char **env);
void	ft_left_red(t_tree *tree, t_data *envi, char **env);
void	ft_r_double_red(t_tree *tree, t_data *envi, char **env);
void	ft_pipe(t_tree *tree, t_data *envi, char **env);
void	ft_l_double_red(t_tree *tree, t_data *envi, char **env);
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		cd(char *path, t_data **envi);
int		echo(char **av);
void	get_environement(char **env, t_data **environement);
void	reset_old_pwd(t_data **envi);
int		env(t_data *envi);
int		check_export_args(char *str, int *status);
int		get_var_lenght(char *str);
int		get_value_lenght(int end, char *str);
int		check_append_new(char *str);
void	create_new_var(t_export *exp, char *av, t_data **envi);
void	no_option_export(t_data *envi);
void	initialize_exp_variable(t_export *var, char *av, t_data *envi);
void	append_operation(t_export *exp, char *av, t_data **envi);
void	create_update(t_export *exp, char *av, t_data **envi);
int		export(char **av, t_data **envi);
int		pwd(void);
void	first_on(t_data **tmp, t_data **environement);
void	last_on(t_data **tmp2, t_data **tmp, t_data **environement);
void	in_middle(t_data **tmp2, t_data **tmp, t_data **environement);
int		check_unset_params(char *str, int *status);
t_data	*get_variable(t_data *envi, char *str);
int		check_pos(t_data *envi, t_data *tmp);
t_data	*get_before(t_data *envi, t_data *tmp);
int		unset(char **av, t_data **environement);
t_data	*ft_mylstnew(char *content, char *content2);
void	ft_lstadd_back(t_data **lst, t_data *new);
t_data	*ft_lstlast(t_data *lst);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_var_value(char *str, int *x, t_data *env, int sig);
char	*remove_quotes(char *str);
int		allocation(char *str, t_data *env);
int		create_new_str(char *str, char *s, int i, t_data *env);
void	expand(t_tree *tree, t_data *env, char **environement);
void	check_builtin(t_tree *tree, t_data *env, char **environement);
int		my_strcmp(char *s1, char *s2);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*my_strjoin(char *s1, char *s2);
void	update_pwd(t_data **env, t_data **tmp, t_data **tmp2, char *str);
int		ft_atoi(char *str);
int		ft_exit(char **av);
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
int		ft_isdigit(int c);
char	*get_cmd(char *s, t_data *env);

#endif
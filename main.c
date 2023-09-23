#include "./libft/libft.h"
#include <stdio.h>
#include "minishell.h"

static int	is_cmd(char c)
{
	if (c!= ' ' && c != '>' && c != '<' && c != '|')
		return (1);
	return (0);
}

int	count_str(char *str)
{
	int			i;
	int		space_count;
	int		count;
	int		flag;

	i = 0;
	space_count = 0;
	count = 0;
	flag = 0;
    str = ft_strtrim(str, " ");
	while (str[i])
	{
		if (str[i] != ' ')
        {
            count++;
            flag = 1;
        }
		else if (str[i] == ' ' && flag)
		{
			space_count++;
			flag = 0;
		}
		i++;
	}
    return (count + space_count);
}

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

void	get_cmd(t_list **cmd, char *str, size_t start, size_t len)
{
	t_list	*cmd2;
	char	*string;
	static	int	flag;

	string = ft_substr(str, start, len);
	if (!flag)
	{
		*cmd = ft_lstnew(string);
		flag = 1;
	}
	else
	{
		cmd2 = ft_lstnew(string);
		ft_lstadd_back(cmd, cmd2);
	}
}

int find_squote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != '\"' && str[i] != '\'')
            i++;
        else
            return (i);
    }
    return (i);
}

int find_equote(char *str, int i)
{
    char c;

    c = str[i];
    i++;
    while (str[i] != c)
        i++;
    return (i);
}

void    organize_args(char *str, t_list **cmd)
{
    
}

static t_list	*creat_list(char *str)
{
	int i;
    int fq;
    int eq;
    int len;
    int start;

    i = 0;
    fq = find_squote(str);
    eq = find_equote(str, fq);
    while (str[i])
    {
        start = i;
        while (i < fq && is_cmd(str[i]))
        {
            
        }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    }
}



int main()
{
   t_list *cmd;
   char *str;

    str = readline("$Minishell : ");
   char *str2 = get_str_ready(str);
   cmd = check_quotes(cmd, str2);
   while (cmd)
   {
    printf("|%s|\n", cmd->content);
    cmd = cmd->next;
   }
   return 0;
}
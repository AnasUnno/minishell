/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:04:34 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/12 17:53:43 by araji-af         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int ac, char **av, char **envi)
{
	(void)ac;
	t_data *envii;
    int     var;
	
    var = 0;
    get_environement(envi, &envii);
    if (!ft_strcmp(av[1], "cd"))
        cd(av[2], &envii);//check cd no options.
    if (!ft_strcmp(av[1], "echo"))
        echo(av + 2);
    if (!ft_strcmp(av[1], "env"))
        env(envii);
    if (!ft_strcmp(av[1], "export"))
        export(av + 2, &envii);
    if (!ft_strcmp(av[1], "pwd"))
        pwd();
    if (!ft_strcmp(av[1], "unset"))
        unset(av + 2, &envii);
    if (!ft_strcmp(av[1], "exit"))
        ft_exit(av + 2);
    // no_option_export(envii);
    return 0;
}
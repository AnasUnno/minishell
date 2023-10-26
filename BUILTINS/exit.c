/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:11:19 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/17 17:58:59 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	atoi_helper(void)
{
	ft_printf("bash: exit: numeric argument required\n");
	exit(255);
}

int	ft_atoi(char *s)
{
	int			sign;
	long long	nb;
	int			n;

	nb = 0;
	sign = 1;
	if (*s == '+')
		s++;
	if (*s == '-' && s++)
		sign = -1;
	while (*s)
	{
		n = (*s - 48) * sign;
		if (nb > (LLONG_MAX / 10) || (nb == (LLONG_MAX / 10) && n > 7))
			atoi_helper();
		if (nb < (LLONG_MIN / 10) || (nb == (LLONG_MIN / 10) && n < -8))
			atoi_helper();
		nb = nb * 10 + n;
		s++;
	}
	return (nb);
}

int	count_arg(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	check_numerique(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '-' && !flag)
		{
			flag = 1;
			i++;
		}
		if (ft_isdigit((int)str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_exit(char **av)
{
	if (!count_arg(av))
		exit(0);
	if (count_arg(av) > 1 && check_numerique(av[0]))
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (av[0] && !check_numerique(av[0]))
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			av[0]);
		exit(255);
	}
	else if (count_arg(av) == 1 && check_numerique(av[0]))
		exit((unsigned char)ft_atoi(av[0]));
	return (0);
}

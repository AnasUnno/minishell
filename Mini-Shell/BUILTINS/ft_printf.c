/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:49:17 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/17 17:59:28 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_format(char half_form)
{
	int		i;
	char	*all_form;

	all_form = "cspdiuxX%";
	i = 0;
	while (all_form[i])
	{
		if (all_form[i] == half_form)
			return (1);
		i++;
	}
	return (0);
}

int	printf_helper(va_list args_ptr, char format_speci)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (format_speci == 'c')
		count += ft_putchar(va_arg(args_ptr, int));
	else if (format_speci == 's')
		count += ft_putstr(va_arg(args_ptr, const char *));
	else if (format_speci == 'd' || format_speci == 'i')
		count += ft_putnbr(va_arg(args_ptr, int));
	else if (format_speci == 'u')
		count += unsigned_forme(va_arg(args_ptr, unsigned int));
	else if (format_speci == 'x')
		count += hexa_lower(va_arg(args_ptr, int));
	else if (format_speci == 'X')
		count += hexa_upper(va_arg(args_ptr, int));
	else if (format_speci == 'p')
	{
		count += ft_putstr("0x");
		count += print_pointer(va_arg(args_ptr, uintptr_t));
	}
	else if (format_speci == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args_ptr;
	int		i;
	int		count;

	va_start(args_ptr, format);
	i = 0;
	if (!format)
		return (0);
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && is_format(format[i + 1]))
		{
			count += printf_helper(args_ptr, format[i + 1]);
			i += 2;
		}
		else
		{
			if (format[i] != '%')
				count += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(args_ptr);
	return (count);
}

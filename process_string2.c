/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:44 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:24:56 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	cycle_arg3(char ch, va_list args, int *result)
{
	unsigned int	value6;

	if (ch == 'x')
	{
		value6 = va_arg(args, unsigned int);
		ft_putnbr_base(value6, "0123456789abcdef", result);
	}
	else if (ch == 'X')
	{
		value6 = va_arg(args, unsigned int);
		ft_putnbr_base(value6, "0123456789ABCDEF", result);
	}
}

void	cycle_args2(char ch, va_list args, int *result)
{
	int				value3;
	unsigned int	value4;
	void			*value5;
	unsigned int	value6;

	if (ch == 'u')
	{
		value4 = va_arg(args, unsigned int);
		ft_putnbr_unsigned(value4, result);
	}
	else if (ch == 'd' || ch == 'i')
	{
		value3 = va_arg(args, int );
		ft_putnbr(value3, result);
	}
	else if (ch == 'p')
	{
		value5 = va_arg(args, void *);
		ft_putptr(value5, result);
	}
	else
		cycle_arg3(ch, args, result);
}

int	work_with_str(char ch, va_list args, int *result)
{
	char	*value2;

	value2 = va_arg(args, char *);
	if (!value2)
	{
		if (write(1, "(null)", 6) == -1)
		{
			*result = -1;
			return (-1);
		}
		(*result) += 6;
	}
	else
	{
		if (ft_putstr(value2, result) == -1)
		{
			*result = -1;
			return (-1);
		}
	}
	return (0);
}

void	cycle_args(char ch, va_list args, int *result)
{
	int		value1;
	char	*value2;
	int		value3;

	if (ch == 'c')
	{
		value1 = va_arg(args, int);
		if (ft_putch((char)value1, result) == -1)
		{
			*result = -1;
			return ;
		}
	}
	else if (ch == 's')
	{
		if (work_with_str(ch, args, result) == -1)
			return ;
	}
	else
		cycle_args2(ch, args, result);
}

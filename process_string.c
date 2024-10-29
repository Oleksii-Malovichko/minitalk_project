/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:18:13 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:24:59 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	check_symbol(char c, const char *sym)
{
	int	j;

	j = 0;
	if (c == '%')
		return (c);
	while (sym[j])
	{
		if (sym[j] == c)
			return (c);
		j++;
	}
	return (0);
}

void	go_to_cycle(const char *str, const char *sym, va_list args, int *result)
{
	char	ch;
	size_t	write_result;

	ch = check_symbol(*str, sym);
	if (ch)
		cycle_args(ch, args, result);
	else
	{
		write_result = write(1, str - 1, 2);
		if (write_result == -1)
		{
			*result = -1;
			return ;
		}
		*result += write_result;
	}
}

int	two_ways(const char *str, const char *sym, va_list args, int *result)
{
	if (*str == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		(*result)++;
	}
	else
	{
		go_to_cycle(str, sym, args, result);
		if (*result == -1)
			return (-1);
	}
	return (0);
}

int	is_right_str(const char *str, const char *sym, va_list args)
{
	int		result;

	result = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (two_ways(str, sym, args, &result) == -1)
				return (-1);
		}
		else
		{
			if (ft_putch(*str, &result) == -1)
				return (-1);
		}
		str++;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:22:42 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:25:52 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putch(const char ch, int *result)
{
	int	write_result;

	write_result = write(1, &ch, 1);
	if (write_result == -1)
	{
		*result = -1;
		return (-1);
	}
	(*result)++;
	return (0);
}

int	ft_putstr(const char *str, int *result)
{
	int	write_result;

	while (*str)
	{
		write_result = write(1, str, 1);
		if (write_result == -1)
		{
			*result = -1;
			return (-1);
		}
		(*result) += write_result;
		str++;
	}
	return (0);
}

int	write_func_char(char ch, int *result)
{
	int	write_result;

	write_result = write(1, &ch, 1);
	if (write_result == -1)
	{
		*result = -1;
		return (-1);
	}
	return (0);
}

int	write_func_str(char *str, int *result, size_t len)
{
	if (write(1, str, len) == -1)
	{
		*result = -1;
		return (-1);
	}
	(*result) += 11;
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:01:44 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:26:03 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long nb, char *base, int *result)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
	{
		ft_putnbr_base(nb / base_len, base, result);
		if (*result == -1)
			return ;
	}
	ft_putch(base[nb % base_len], result);
}

void	ft_putptr(void *ptr, int *result)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	if (ptr == NULL)
	{
		if (write(1, "0x0", 3) == -1)
		{
			*result = -1;
			return ;
		}
		*result += 3;
	}
	else
	{
		if (write(1, "0x", 2) == -1)
		{
			*result = -1;
			return ;
		}
		(*result) += 2;
		ft_putnbr_base(addr, "0123456789abcdef", result);
	}
}

void	ft_putnbr_unsigned(unsigned int nb, int *result)
{
	char	ch;

	if (nb == 0)
	{
		if (write(1, "0", 1) == -1)
		{
			*result = -1;
			return ;
		}
		(*result)++;
		return ;
	}
	if (nb >= 10)
	{
		ft_putnbr_unsigned(nb / 10, result);
		if (*result == -1)
			return ;
	}
	ch = (nb % 10) + '0';
	if (write(1, &ch, 1) == -1)
	{
		*result = -1;
		return ;
	}
	(*result)++;
}

void	ft_putnbr(int nb, int *result)
{
	if (nb == -2147483648)
	{
		if (write_func_str("-2147483648", result, 11) == -1)
			return ;
		return ;
	}
	if (nb < 0)
	{
		if (write_func_char('-', result) == -1)
			return ;
		(*result)++;
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, result);
		if (*result == -1)
			return ;
	}
	if (write_func_char((nb % 10) + '0', result) == -1)
		return ;
	(*result)++;
}

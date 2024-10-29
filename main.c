/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:27:44 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:21:55 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	const char	*sym;
	int			result;
	va_list		args;

	sym = "cspdiuxX%";
	va_start(args, str);
	result = is_right_str(str, sym, args);
	va_end(args);
	return (result);
}

/* int main()
{
	printf("%d\n", ft_printf("%d\n", 10));
	printf("%d\n", printf("%d\n", 10));
	// printf("%d\n", ft_printf("\001\002\007\v\010\f\r\n"));
} */

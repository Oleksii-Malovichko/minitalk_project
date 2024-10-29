/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:27:52 by omalovic          #+#    #+#             */
/*   Updated: 2024/10/22 14:29:13 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

char	check_symbol(char c, const char *sym);
int		is_right_str(const char *str, const char *sym, va_list args);
int		ft_printf(const char *str, ...);
int		ft_putch(const char ch, int *result);
int		ft_putstr(const char *str, int *result);
void	ft_putnbr_base(unsigned long nb, char *base, int *result);
void	ft_putptr(void *ptr, int *result);
void	ft_putnbr(int nb, int *result);
void	ft_putnbr_unsigned(unsigned int nb, int *result);
int		ft_strlen(char *str);
void	cycle_arg3(char ch, va_list args, int *result);
void	go_to_cycle(const char *str, const char *sym,
			va_list args, int *result);
int		write_func_str(char *str, int *result, size_t len);
int		write_func_char(char ch, int *result);
void	cycle_args(char ch, va_list args, int *result);

#endif
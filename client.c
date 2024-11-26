/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:59 by alex              #+#    #+#             */
/*   Updated: 2024/11/26 15:14:07 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

void	send_bit(int pid, int bit)
{
	usleep(300);
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			stop_programm(1);
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			stop_programm(1);
	}
}

void	send_char(int pid, char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		send_bit(pid, bit);
		i++;
	}
}

void	work_str(int pid, char *str, char *size)
{
	int	i;

	i = 0;
	while (size[i] != '\0')
	{
		send_char(pid, size[i]);
		i++;
	}
	send_char(pid, '\0');
	i = 0;
	while (str[i] != '\0')
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	exit(EXIT_SUCCESS);
}

int	main(int n, char *args[])
{
	int	pid;

	if (n != 3)
		stop_programm(1);
	pid = ft_atoi2(args[1]);
	work_str(pid, args[2], ft_itoa(ft_strlen(args[2])));
	return (0);
}

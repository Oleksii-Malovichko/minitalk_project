/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:59 by alex              #+#    #+#             */
/*   Updated: 2024/11/25 17:35:06 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_ack_received = 0;

void	handle_ack(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	wait_for_ack(void)
{
	while (!g_ack_received)
		pause();
	g_ack_received = 0;
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

void	work_str(int pid, char *str)
{
	int	i;

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
	int					pid;
	struct sigaction	sa;

	if (n != 3)
		stop_programm(1);
	sa = (struct sigaction){0};
	pid = ft_atoi2(args[1]);
	sa.sa_flags = 0;
	sa.sa_handler = handle_ack;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	// work_str(pid, ft_itoa(ft_strlen(args[2])));
	// return (0);
	work_str(pid, args[2]);
	return (0);
}

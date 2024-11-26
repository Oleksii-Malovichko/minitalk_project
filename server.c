/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:07:08 by alex              #+#    #+#             */
/*   Updated: 2024/11/26 15:33:12 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_received_len = 0;

void	stop_programm(int i, t_server_state **state1)
{
	if (*state1)
	{
		free(*state1);
		*state1 = NULL;
	}
	if (i == 0)
		exit(EXIT_SUCCESS);
	if (i == 1)
		exit(EXIT_FAILURE);
}

int	handle_char(t_server_state **state, char **buffer)
{
	static int	i = 0;

	if ((*state)->current_value == '\0')
	{
		free(*state);
		*state = NULL;
		ft_putstr2(*buffer);
		write(1, "\n", 1);
		free(*buffer);
		*buffer = 0;
		g_received_len = 0;
		i = 0;
		return (0);
	}
	else
		(*buffer)[i] = (*state)->current_value;
	i++;
	(*state)->current_value = 0;
	(*state)->bit_index = 0;
	return (1);
}

int	receive_len(int sig, t_server_state **state)
{
	static int	len = 0;
	int			temp;
	char		num_ch;

	if (sig == SIGUSR2)
		(*state)->current_value |= (1 << (*state)->bit_index);
	(*state)->bit_index++;
	if ((*state)->bit_index == 8)
	{
		if ((*state)->current_value == '\0')
		{
			g_received_len = 1;
			temp = len;
			len = 0;
			(*state)->bit_index = 0;
			(*state)->current_value = 0;
			return (temp);
		}
		num_ch = ((*state)->current_value);
		len = len * 10 + (num_ch - '0');
		(*state)->bit_index = 0;
		(*state)->current_value = 0;
	}
	return (0);
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_server_state	*state = NULL;
	static char				*buffer = NULL;

	(void)context;
	if (!state)
	{
		state = ft_calloc(1, sizeof(t_server_state));
		state->bit_index = 0;
		state->current_value = 0;
		state->pid = info->si_pid;
	}
	if (g_received_len == 0)
		give_mem(sig, &state, &buffer);
	else
	{
		if (sig == SIGUSR2)
			state->current_value |= (1 << state->bit_index);
		state->bit_index++;
		if (state->bit_index == 8)
		{
			if (!handle_char(&state, &buffer))
				return ;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_flags = 0;
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause ();
}

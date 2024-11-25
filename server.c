/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:07:08 by alex              #+#    #+#             */
/*   Updated: 2024/11/25 18:50:39 by omalovic         ###   ########.fr       */
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

int	handle_char(t_server_state **state)
{
	if ((*state)->current_value == '\0')
	{
		write(1, "\n", 1);
		free(*state);
		*state = NULL;
		g_received_len = 0;
		return (0);
	}
	else
		write(1, &(*state)->current_value, 1);
	(*state)->current_value = 0;
	(*state)->bit_index = 0;
	return (1);
}

void	receive_len(int sig, t_server_state **state, char **buffer)
{
	static int len = 0;
	char num_ch;
	
	*buffer = NULL;
	if (sig == SIGUSR2)
		(*state)->current_value |= (1 << (*state)->bit_index);
	(*state)->bit_index++;
	if ((*state)->bit_index == 8)
	{
		if ((*state)->current_value == '\0')
		{
			g_received_len = 1;
			ft_printf("len: %d\n", len);
			len = 0;
			(*state)->bit_index = 0;
			(*state)->current_value = 0;
			return ;
		}
		num_ch = ((*state)->current_value);
		len += num_ch - '0';
		printf("num_ch %c\n", num_ch);
		printf("len %d\n", len);
		(*state)->bit_index = 0;
		(*state)->current_value = 0;
	}
	// if (g_received_len == 1)
	// 	return;
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static t_server_state	*state = NULL;
	static char				*buffer = NULL;
	
	(void)context;
	if (!state)
	{
		state = ft_calloc(1, sizeof(t_server_state));
		if (!state)
			stop_programm(1, &state);
		state->bit_index = 0;
		state->current_value = 0;
		state->pid = info->si_pid;
	}
	if (g_received_len == 0)
		receive_len(sig, &state, &buffer);
	else
	{
		if (sig == SIGUSR2)
			state->current_value |= (1 << state->bit_index);
		state->bit_index++;
		if (state->bit_index == 8)
		{
			if (!handle_char(&state))
				return ;
		}
	}
	// if (sig == SIGUSR2)
	// 	state->current_value |= (1 << state->bit_index);
	// state->bit_index++;
	// if (state->bit_index == 8)
	// {
	// 	if (!handle_char(&state))
	// 		return ;
	// }
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("%d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause ();
}

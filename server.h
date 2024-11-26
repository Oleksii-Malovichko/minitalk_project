/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:06:31 by alex              #+#    #+#             */
/*   Updated: 2024/11/26 15:35:46 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"

int		ft_atoi1(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_putstr2(char *buffer);

typedef struct s_server_state
{
	int		bit_index;
	char	current_value;
	int		pid;
}		t_server_state;

int		receive_len(int sig, t_server_state **state);
void	give_mem(int sig, t_server_state **state, char **buffer);
void	stop_programm(int i, t_server_state **state1);

#endif

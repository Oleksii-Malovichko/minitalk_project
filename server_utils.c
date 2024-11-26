/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:40:24 by alex              #+#    #+#             */
/*   Updated: 2024/11/26 15:33:28 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	ft_atoi1(const char *str)
{
	unsigned long		num;
	int					sign;
	size_t				i;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
		break ;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

void	give_mem(int sig, t_server_state **state, char **buffer)
{
	int	len;

	len = receive_len(sig, state);
	if (len > 0)
	{
		*buffer = malloc(sizeof(char) * (len + 1));
		if (!*buffer)
			stop_programm(1, state);
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_size;
	void			*ptr;
	unsigned char	*byte_ptr;
	size_t			i;

	i = 0;
	total_size = count * size;
	ptr = (void *) malloc (total_size);
	if (ptr == NULL)
	{
		exit(EXIT_FAILURE);
	}
	byte_ptr = ptr;
	while (i < total_size)
	{
		byte_ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

void	ft_putstr2(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		write(1, &buffer[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

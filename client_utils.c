/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omalovic <omalovic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:41:10 by alex              #+#    #+#             */
/*   Updated: 2024/11/25 17:43:56 by omalovic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	ft_atoi2(const char *str)
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

void	stop_programm(int i)
{
	if (i == 0)
		exit(EXIT_SUCCESS);
	if (i == 1)
		exit(EXIT_FAILURE);
}

void	send_bit(int pid, int bit)
{
	usleep(200);
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
	// wait_for_ack();
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

int	get_length(int n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		length++;
	}
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	if (length == 0)
		return (1);
	return (length);
}

char	*ft_strdup1(const char *s1)
{
	int		len_s1;
	char	*s2;
	int		i;

	len_s1 = 0;
	i = 0;
	while (s1[len_s1] != '\0')
	{
		len_s1++;
	}
	s2 = (char *)malloc(sizeof(char) * (len_s1 + 1));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (i < len_s1)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		length;

	if (n == -2147483648)
		return (ft_strdup1("-2147483648"));
	length = get_length(n);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	if (n == 0)
		result[0] = '0';
	length--;
	while (n > 0)
	{
		result[length] = (n % 10) + '0';
		n /= 10;
		length--;
	}
	return (result);
}

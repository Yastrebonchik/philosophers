/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:37:42 by kcedra            #+#    #+#             */
/*   Updated: 2020/12/30 15:27:57 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_atoi(const char *str)
{
	int		i;
	char	sign;
	int		number;

	i = 0;
	number = 0;
	while (str[i] > 0 && str[i] < 33 && str[i] != '\0' && str[i] != 27)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i];
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10;
		number += str[i] - 48;
		i++;
	}
	if (sign == '-')
		number = number * (-1);
	return (number);
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr;
	int		flag;

	flag = 0;
	if (n == -2147483648)
	{
		flag++;
		n++;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * (-1);
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	nbr = (n % 10) + 48;
	if (flag == 1)
		nbr = '8';
	write(fd, &nbr, 1);
}

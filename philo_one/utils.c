/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:37:42 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/02 00:00:43 by yastrebon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_atoi(const char *str)
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

void			ft_putstr_fd(char *s, int fd)
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

void			ft_putnbr_fd(int n, int fd)
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

void			print_state(char *phrase, int phil_num)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	ft_putnbr_fd((tv.tv_sec - g_time.tv_sec) * 1000 +
	(tv.tv_usec - g_time.tv_usec) / 1000, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(phil_num, 1);
	ft_putstr_fd(phrase, 1);
}

unsigned int	ft_abs_substract(int a, int b)
{
	int	res;

	res = a - b;
	if (res < 0)
		res = res * (-1);
	return (res);
}
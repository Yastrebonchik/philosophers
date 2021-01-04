/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:37:42 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/04 22:53:07 by kcedra           ###   ########.fr       */
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
	pthread_mutex_lock(&g_print_mutex);
	ft_putnbr_fd((tv.tv_sec - g_time.tv_sec) * 1000 +
	(tv.tv_usec - g_time.tv_usec) / 1000, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(phil_num, 1);
	ft_putstr_fd(phrase, 1);
	pthread_mutex_unlock(&g_print_mutex);
}

int				msleep(t_mseconds time)
{
	t_time		tv;
	t_mseconds	start;
	t_mseconds	now;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	now = start;
	while (now - start < time)
	{
		usleep(100);
		if (gettimeofday(&tv, NULL) == -1)
			return (0);
		now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
	return (1);
}

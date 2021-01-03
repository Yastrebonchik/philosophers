/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:37:42 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/04 01:35:44 by yastrebon        ###   ########.fr       */
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

int				my_usleep(t_mseconds time)
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

int				eat_trigger(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[0].philo_quan)
	{
		if (philos[i++].num_of_times_eat != 0)
			return (1);
	}
	return (0);
}

void			mutex_init(t_philo **philos)
{
	int				i;
	pthread_mutex_t *mutex;

	i = 0;
	mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * (((*philos)[0]).philo_quan));
	while (i < ((*philos)[0].philo_quan))
		pthread_mutex_init(&mutex[i++], NULL);
	i = 0;
	while (i < ((*philos)[0].philo_quan))
	{
		(*philos)[i].left_fork = &(mutex[i]);
		if ((*philos)[i].philo_num == (*philos)[0].philo_quan)
			(*philos)[i].right_fork = &(mutex[0]);
		else
			(*philos)[i].right_fork = &(mutex[i + 1]);
		i++;
	}
}

void			mutex_destroy(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < ((*philos)[0].philo_quan))
		pthread_mutex_destroy((*philos)[i++].left_fork);
}

void			philo_init(t_philo **philos, int *params, int argc)
{
	int	i;

	i = 0;
	(*philos) = (t_philo*)malloc(sizeof(t_philo) * params[0]);
	while (i < params[0])
	{
		((*philos)[i]).philo_num = i + 1;
		((*philos)[i]).philo_quan = params[0];
		((*philos)[i]).time_to_die = params[1];
		((*philos)[i]).time_to_eat = params[2];
		((*philos)[i]).time_to_sleep = params[3];
		((*philos)[i]).num_of_times_eat = 0;
		((*philos)[i]).eat_trigger = 0;
		if (argc == 6)
			((*philos)[i]).num_of_times_eat = params[4];
		i++;
	}
}

void			supervisor_init(t_philo **philos)
{
	int			i;
	pthread_t	*sv;

	i = 0;
	sv = (pthread_t*)malloc(sizeof(pthread_t) * (*philos)[0].philo_quan);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(sv[i]), NULL, supervisor, (void*)&((*philos)[i])) != 0)
		{
			ft_putstr_fd("Threading error", 1);
			exit(0);
		}
		(*philos)[i].supervisor = &(sv[i]);
		i++;
		usleep(100);
	}
}

void			threads_init(t_philo **philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = (pthread_t*)malloc(sizeof(pthread_t) * (*philos)[0].philo_quan);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(threads[i]), NULL, philo, (void*)&((*philos)[i])) != 0)
		{
			ft_putstr_fd("Threading error", 1);
			exit(0);
		}
		(*philos)[i].thread = &(threads[i]);
		i++;
		usleep(100);
	}
}

void			threads_join(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < ((*philos)[0].philo_quan))
	{
		pthread_join(*(*philos)[i].thread, NULL);
		pthread_join(*(*philos)[i].supervisor, NULL);
		i++;
	}
}

int			check_eat_trigger(t_philo *philos, int i)
{
	while (i < philos[0].philo_quan)
	{
		if (philos[i].eat_trigger == 1)
			return (0);
		i += 2;
	}
	return (1);
}

void			set_eat_trigger(t_philo *philos, int i)
{
	while (i < philos[0].philo_quan)
	{
		philos[i].eat_trigger = 0;
		i += 2;
	}
}
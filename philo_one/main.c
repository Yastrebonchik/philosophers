/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:31 by alexander         #+#    #+#             */
/*   Updated: 2021/01/04 00:06:48 by yastrebon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*waiter(void *arr)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo*)arr;
	if (philos[0].philo_quan % 2 == 0)
	{
		if (philos[0].num_of_times_eat != 0)
		{
			while (eat_trigger(philos))
			{
				i = 0;
				while (i < philos[0].philo_quan)
				{
					philos[i].left_fork_trigger = 1;
					philos[i].right_fork_trigger = 1;
					i += 2;
				}
				my_usleep(philos[0].time_to_eat);
				i = 1;
				while (i < philos[0].philo_quan)
				{
					philos[i].left_fork_trigger = 1;
					philos[i].right_fork_trigger = 1;
					i += 2;
				}
				my_usleep(philos[0].time_to_eat);
			}
			exit(0);
		}
		else
		{
			while (1)
			{
				i = 0;
				while (i < philos[0].philo_quan)
				{
					philos[i].left_fork_trigger = 1;
					philos[i].right_fork_trigger = 1;
					i += 2;
				}
				i = 1;
				my_usleep(philos[0].time_to_eat - 1);
				while (i < philos[0].philo_quan)
				{
					philos[i].left_fork_trigger = 1;
					philos[i].right_fork_trigger = 1;
					i += 2;
				}
				my_usleep(philos[0].time_to_eat - 1);
			}
		}
	}
	return NULL;
}

void	*supervisor(void *arr)
{
	int		time_to_die;
	t_philo	*philo;

	philo = (t_philo*)arr;
	time_to_die = philo->time_to_die;
	while (time_to_die > 0)
	{
		time_to_die = time_to_die - 1;
		if (g_death_trigger[philo->philo_num] == 1)
		{
			g_death_trigger[philo->philo_num] = 0;
			time_to_die = philo->time_to_die;;
		}
		my_usleep(1);
	}
	print_state(" is died\n", philo->philo_num);
	exit(0);
}

void	*philo(void *arr)
{
	t_philo	*philo;

	philo = (t_philo*)arr;
	while (1)
	{
		print_state(" is thinking\n", philo->philo_num);
		while (philo->left_fork_trigger == 0)
			usleep(100);
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_trigger = 0;
		usleep(philo->philo_num * 100);
		print_state(" has taken a fork\n", philo->philo_num);
		while (philo->right_fork_trigger == 0)
			usleep(100);
		usleep(philo->philo_num * 100);
		pthread_mutex_lock(philo->right_fork);
		print_state(" has taken a fork\n", philo->philo_num);
		philo->right_fork_trigger = 0;
		g_death_trigger[philo->philo_num] = 1;
		usleep(philo->philo_num * 100);
		print_state(" is eating\n", philo->philo_num);
		my_usleep(philo->time_to_eat);
		if (philo->num_of_times_eat != 0)
			philo->num_of_times_eat -= 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep(philo->philo_num * 100);
		print_state(" is sleeping\n", philo->philo_num);
		my_usleep(philo->time_to_sleep);
		usleep(philo->philo_num * 100);
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	int			i;
	int			j;
	int			*params;
	pthread_t	wt;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (0);
	}
	gettimeofday(&g_time, NULL);
	i = 1;
	j = 0;
	params = (int*)malloc(sizeof(int) * (argc));
	while (i < argc)
		params[j++] = ft_atoi(argv[i++]);
	philos = NULL;
	i = 0;
	g_death_trigger = (int*)malloc(sizeof(int)* (params[0]));
	while (i < params[0])
		g_death_trigger[i++]= 0;
	philo_init(&philos, params, argc);
	mutex_init(&philos); 
	pthread_create(&wt, NULL, waiter, (void*)philos);
	supervisor_init(&philos);
	threads_init(&philos);
	threads_join(&philos);
	mutex_destroy(&philos);
	return (0);
}

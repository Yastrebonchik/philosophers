/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:31 by alexander         #+#    #+#             */
/*   Updated: 2021/01/03 19:00:33 by yastrebon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// void	*waiter(void *arr)
// {
// 	int	*array;

// 	array = (int*)arr;
// 	if (array[0] % 2 == 0)
// 	{
// 		while (g_counter < array[4])
// 		{
// 			g_mutex_trigger = 1;
// 		}
// 	}
// }

void	*supervisor(void *arr)
{
	int		time_to_die;
	t_philo	*philo;

	philo = (t_philo*)arr;
	time_to_die = philo->time_to_die;
	while (time_to_die > 0)
	{
		time_to_die = time_to_die - 1;
		if (g_death_trigger == 1)
		{
			g_death_trigger = 0;
			time_to_die = philo->time_to_die;;
		}
		my_usleep(1);
	}
	print_state(" is died\n", 1);
	exit(0);
}

void	*philo(void *arr)
{
	t_philo	*philo;

	philo = (t_philo*)arr;
	while (1)
	{
		ft_putnbr_fd(pthread_mutex_lock(philo->left_fork), 1);
		ft_putstr_fd("\n", 1);
		print_state(" has taken a fork\n", 1);
		ft_putnbr_fd(pthread_mutex_lock(philo->right_fork), 1);
		ft_putstr_fd("\n", 1);
		print_state(" has taken a fork\n", 1);
		g_death_trigger = 1;
		print_state(" is eating\n", 1);
		my_usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_state(" is sleeping\n", 1);
		my_usleep(philo->time_to_sleep);
		g_counter++;
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	int			i;
	int			j;
	int			*params;
	t_philo		*philos;
	pthread_t	t1, sv;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (0);
	}
	g_counter = 0;
	g_death_trigger = 0;
	gettimeofday(&g_time, NULL);
	i = 1;
	j = 0;
	params = (int*)malloc(sizeof(int) * (argc));
	while (i < argc)
		params[j++] = ft_atoi(argv[i++]);
	philos = NULL;
	//printf("Time to eat = %d and time do sleep = %d and number to eat = %d\n", params[2], params[3], params[4]);
	philo_init(philos, params, argc);
	mutex_init(philos); 
	pthread_create(&sv, NULL, supervisor, (void*)&(philos[0]));
	pthread_create(&t1, NULL, philo, (void*)&(philos[0]));
	pthread_join(t1, NULL);
	ft_putstr_fd("Hello world!\n", 1);
	mutex_destroy(philos);
	return (0);
}

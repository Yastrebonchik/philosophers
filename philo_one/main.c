/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:31 by alexander         #+#    #+#             */
/*   Updated: 2021/01/02 00:17:58 by yastrebon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


void	supervisor(void *arr)
{
	int		*array;
	int		time_to_die;

	array = (int*)arr;
	time_to_die = array[1];
	while (time_to_die > 0)
	{
		time_to_die = time_to_die - 10;
		if (g_trigger == 1)
		{
			g_trigger = 0;
			time_to_die = array[1];
		}
		usleep(10000);
	}
	print_state(" is died\n", 1);
	exit(0);
}

void	*print_test(void *arr)
{
	int				*array;
	//t_time			tv;

	array = (int*)arr;
	while (g_counter < array[4])
	{
		pthread_mutex_lock(&(g_mutex[0]));
		print_state(" has taken a fork\n", 1);
		pthread_mutex_lock(&(g_mutex[1]));
		print_state(" has taken a fork\n", 1);
		g_trigger = 1;
		print_state(" is eating\n", 1);
		usleep(array[2] * 1000);
		pthread_mutex_unlock(&(g_mutex[0]));
		pthread_mutex_unlock(&(g_mutex[1]));
		print_state(" is sleeping\n", 1);
		usleep(array[3] * 1000);
		g_counter++;
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	int			i;
	int			j;
	int			*params;
	pthread_t	t1;//, sv;

	g_counter = 0;
	g_trigger = 0;
	gettimeofday(&g_time, NULL);
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (0);
	}
	i = 1;
	j = 0;
	params = (int*)malloc(sizeof(int) * (argc));
	while (i < argc)
	{
		params[j] = ft_atoi(argv[i]);
		i++;
		j++;
	}
	printf("Time to eat = %d and time do sleep = %d and number to eat = %d\n", params[2], params[3], params[4]); 
	g_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 2);
	pthread_mutex_init(&(g_mutex[0]), NULL);
	pthread_mutex_init(&(g_mutex[1]), NULL);
	//pthread_create(&sv, NULL, supervisor, (void*)params);
	pthread_create(&t1, NULL, print_test, (void*)params);
	supervisor((void*)params);
	//pthread_create(&t2, NULL, print_test, (void*)params);
	pthread_join(t1, NULL);
	//pthread_join(t2, NULL);
	ft_putstr_fd("Hello world!\n", 1);
	pthread_mutex_destroy(&(g_mutex[0]));
	pthread_mutex_destroy(&(g_mutex[1]));
	return (0);
}

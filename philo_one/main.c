/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:31 by alexander         #+#    #+#             */
/*   Updated: 2020/12/30 22:54:23 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

pthread_mutex_t g_mutex;

void	*print_test(void *arr)
{
	int				i;
	int				*array;
	
	array = (int*)arr;
	i = 1;
	while (array[i] == 5)
	{
		pthread_mutex_lock(&g_mutex);
		ft_putnbr_fd(array[i], 1);
		write(1, "\n-------------\n", 1);
		pthread_mutex_unlock(&g_mutex);
		usleep(1000000);
		i++;
	}
	return NULL;
}

int		main(int argc, char **argv)
{
	int		i;
	int		*params;
	pthread_t	t1, t2;

	pthread_mutex_init(&g_mutex, NULL);
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (0);
	}
	i = 1;
	params = (int*)malloc(sizeof(int) * (argc)); 
	while (i < argc)
	{
		params[i] = ft_atoi(argv[i]);
		i++;
	}
	pthread_create(&t1, NULL, print_test, (void*)params);
	pthread_create(&t2, NULL, print_test, (void*)params);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	ft_putstr_fd("Hello world!\n", 1);
	return (0);
}

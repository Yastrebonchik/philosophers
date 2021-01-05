/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:40:07 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/05 23:20:06 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				philo_init(t_philo **philos, int *params, int argc)
{
	int	i;

	i = 0;
	g_death = 0;
	if (!((*philos) = (t_philo*)malloc(sizeof(t_philo) * params[0])))
		return (1);
	while (i < params[0])
	{
		((*philos)[i]).philo_num = i + 1;
		((*philos)[i]).philo_quan = params[0];
		((*philos)[i]).time_to_die = params[1];
		((*philos)[i]).time_to_eat = params[2];
		((*philos)[i]).time_to_sleep = params[3];
		((*philos)[i]).num_of_times_eat = 0;
		((*philos)[i]).argc = argc;
		if (argc == 6)
			((*philos)[i]).num_of_times_eat = params[4];
		i++;
	}
	i = 1;
	if (!(g_death_trigger = (int*)malloc(sizeof(int) * (params[0] + 1))))
		return (1);
	while (i < params[0] + 1)
		g_death_trigger[i++] = 0;
	return (0);
}

int				supervisor_init(t_philo **philos)
{
	int			i;
	pthread_t	*sv;

	i = 0;
	if (!(sv = (pthread_t*)malloc(sizeof(pthread_t) * (*philos)[0].philo_quan)))
		return (1);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(sv[i]), NULL, supervisor,
		(void*)&((*philos)[i])) != 0)
			return (1);
		(*philos)[i].supervisor = &(sv[i]);
		i++;
		usleep(100);
	}
	return (0);
}

int				threads_init(t_philo **philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	if (!(threads = (pthread_t*)malloc(sizeof(pthread_t) *
	(*philos)[0].philo_quan)))
		return (1);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(threads[i]), NULL, philo,
		(void*)&((*philos)[i])) != 0)
			return (1);
		(*philos)[i].thread = &(threads[i]);
		i++;
		usleep(100);
	}
	return (0);
}

int				semaphore_init(t_philo **philos)
{
	sem_unlink("/g_death_semaphore");
	sem_unlink("/g_print_semaphore");
	sem_unlink("/g_fork_semaphore");
	g_death_semaphore = sem_open("/g_death_semaphore", O_CREAT, S_IRWXU, 1);
	g_print_semaphore = sem_open("/g_print_semaphore", O_CREAT, S_IRWXU, 1);
	g_fork_semaphore = sem_open("/g_fork_semaphore", O_CREAT, S_IRWXU, 
	(*philos)[0].philo_quan);
	printf("(*philos)[0].philo_quan) = %d\n", (*philos)[0].philo_quan);
	if (g_death_semaphore == NULL || g_print_semaphore == NULL ||
	g_fork_semaphore == NULL)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:30:54 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/05 16:37:25 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			philo_init(t_philo **philos, int *params, int argc)
{
	int	i;

	i = 0;
	if (!((*philos) = (t_philo*)malloc(sizeof(t_philo) * params[0])))
		errors_handling(MALLOC_ERROR);
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
		errors_handling(MALLOC_ERROR);
	while (i < params[0] + 1)
		g_death_trigger[i++] = 0;
}

void			supervisor_init(t_philo **philos)
{
	int			i;
	pthread_t	*sv;

	i = 0;
	if (!(sv = (pthread_t*)malloc(sizeof(pthread_t) * (*philos)[0].philo_quan)))
		errors_handling(MALLOC_ERROR);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(sv[i]), NULL, supervisor,
		(void*)&((*philos)[i])) != 0)
		{
			ft_putstr_fd("Threading error", 1);
			exit(0);
		}
		(*philos)[i].supervisor = &(sv[i]);
		i++;
		if (usleep(40) == -1)
			errors_handling(USLEEP_ERROR);
	}
}

void			threads_init(t_philo **philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	if (!(threads = (pthread_t*)malloc(sizeof(pthread_t) *
	(*philos)[0].philo_quan)))
		errors_handling(MALLOC_ERROR);
	while (i < ((*philos)[0].philo_quan))
	{
		if (pthread_create(&(threads[i]), NULL, philo,
		(void*)&((*philos)[i])) != 0)
		{
			ft_putstr_fd("Threading error", 1);
			exit(0);
		}
		(*philos)[i].thread = &(threads[i]);
		i++;
		if (usleep(40) == -1)
			errors_handling(USLEEP_ERROR);
	}
}

void			mutex_init(t_philo **philos)
{
	int				i;
	pthread_mutex_t *mutex;

	i = 0;
	if (!(mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
	(((*philos)[0]).philo_quan))))
		errors_handling(MALLOC_ERROR);
	while (i < ((*philos)[0].philo_quan))
	{
		pthread_mutex_init(&((*philos)[i]).death_mutex, NULL);
		pthread_mutex_init(&mutex[i++], NULL);
	}
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
	pthread_mutex_init(&g_print_mutex, NULL);
}

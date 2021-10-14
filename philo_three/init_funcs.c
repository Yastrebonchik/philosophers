/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:12:06 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:53 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				philo_init(t_philo **philos, int *params, int argc)
{
	int	i;

	i = 0;
	g_death_counter = 0;
	gettimeofday(&g_time, NULL);
	if (!((*philos) = (t_philo*)malloc(sizeof(t_philo) * params[0])))
		return (1);
	while (i < params[0])
	{
		((*philos)[i]).philo_num = i + 1;
		((*philos)[i]).philo_quan = params[0];
		((*philos)[i]).time_to_die = params[1];
		((*philos)[i]).time_to_eat = params[2];
		((*philos)[i]).time_to_sleep = params[3];
		((*philos)[i]).death_trigger = 0;
		((*philos)[i]).num_of_times_eat = 0;
		((*philos)[i]).argc = argc;
		if (argc == 6)
			((*philos)[i]).num_of_times_eat = params[4];
		i++;
	}
	return (0);
}

int				process_init(t_philo **philos)
{
	int			i;
	pid_t		*processes;

	if (!(processes = (pid_t*)malloc(sizeof(pid_t) * (*philos)[0].philo_quan)))
		return (1);
	i = 0;
	while (i < ((*philos)[0].philo_quan))
	{
		processes[i] = fork();
		if (processes[i] < 0)
			return (1);
		else if (processes[i] == 0)
			philo((void*)&((*philos)[i]));
		i++;
		usleep(100);
	}
	parent_process(processes, *philos);
	return (0);
}

int				semaphore_init(t_philo **philos)
{
	sem_unlink("g_death_semaphore");
	sem_unlink("g_print_semaphore");
	sem_unlink("g_fork_semaphore");
	g_death_semaphore = sem_open("g_death_semaphore", O_CREAT, S_IRWXU, 1);
	g_print_semaphore = sem_open("g_print_semaphore", O_CREAT, S_IRWXU, 1);
	g_fork_semaphore = sem_open("g_fork_semaphore", O_CREAT, S_IRWXU,
	(*philos)[0].philo_quan);
	if (g_print_semaphore == NULL || g_fork_semaphore == NULL
	|| g_death_semaphore == NULL)
		return (1);
	return (0);
}

int				args_check(int **params, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!((*params) = (int*)malloc(sizeof(int) * (argc))))
	{
		ft_putstr_fd("Malloc error\n", 2);
		return (1);
	}
	while (i < argc)
		(*params)[j++] = ft_atoi(argv[i++]);
	i = 0;
	while (i < argc - 1)
	{
		if ((*params)[i] <= 0)
		{
			ft_putstr_fd("Wrong arguments!\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

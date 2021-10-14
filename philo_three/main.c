/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:10:38 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:53 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*supervisor(void *arr)
{
	int		time_to_die;
	t_philo	*philo;

	philo = (t_philo*)arr;
	time_to_die = philo->time_to_die;
	while (time_to_die > 0)
	{
		time_to_die = time_to_die - 1;
		sem_wait(g_death_semaphore);
		if (philo->death_trigger == 1)
		{
			philo->death_trigger = 0;
			time_to_die = philo->time_to_die;
		}
		sem_post(g_death_semaphore);
		msleep(1);
	}
	if (philo->death_trigger != 2)
	{
		print_state(" is died\n", philo->philo_num);
		exit(1);
	}
	return (NULL);
}

void	philo(void *arr)
{
	t_philo	*philo;

	philo = (t_philo*)arr;
	pthread_create(&(philo->supervisor), NULL, &supervisor, philo);
	while (cycle_condition(philo))
	{
		print_state(" is thinking\n", philo->philo_num);
		sem_wait(g_fork_semaphore);
		print_state(" has taken a fork\n", philo->philo_num);
		sem_wait(g_fork_semaphore);
		print_state(" has taken a fork\n", philo->philo_num);
		sem_wait(g_death_semaphore);
		philo->death_trigger = 1;
		sem_post(g_death_semaphore);
		print_state(" is eating\n", philo->philo_num);
		msleep(philo->time_to_eat);
		sem_post(g_fork_semaphore);
		sem_post(g_fork_semaphore);
		philo->num_of_times_eat -= 1;
		if (philo->argc == 6 && philo->num_of_times_eat == 0)
			break ;
		print_state(" is sleeping\n", philo->philo_num);
		msleep(philo->time_to_sleep);
	}
	exit(2);
}

int		main(int argc, char **argv)
{
	int			*params;
	t_philo		*philos;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Wrong number of arguments!\n", 1);
		return (1);
	}
	params = NULL;
	if (args_check(&params, argc, argv) == 1)
		return (0);
	if (philo_init(&philos, params, argc) == 1 || semaphore_init(&philos) == 1
	|| process_init(&philos) == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:38:08 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:56 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		if (g_death_trigger[philo->philo_num] == 1)
		{
			g_death_trigger[philo->philo_num] = 0;
			time_to_die = philo->time_to_die;
		}
		sem_post(g_death_semaphore);
		msleep(1);
	}
	if (check_death(philo))
	{
		print_state(" is died\n", philo->philo_num);
		g_death = 1;
	}
	return (NULL);
}

void	*philo(void *arr)
{
	t_philo	*philo;

	philo = (t_philo*)arr;
	while (cycle_condition(philo))
	{
		print_state(" is thinking\n", philo->philo_num);
		sem_wait(g_fork_semaphore);
		print_state(" has taken a fork\n", philo->philo_num);
		sem_wait(g_fork_semaphore);
		print_state(" has taken a fork\n", philo->philo_num);
		sem_wait(g_death_semaphore);
		g_death_trigger[philo->philo_num] = 1;
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
	g_death_trigger[philo->philo_num] = 2;
	return (NULL);
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
	|| supervisor_init(&philos) == 1 || threads_init(&philos) == 1)
		return (1);
	while (check_death(philos))
	{
		if (g_death == 1)
			break ;
	}
	return (0);
}

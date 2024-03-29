/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:31 by alexander         #+#    #+#             */
/*   Updated: 2021/01/06 23:42:49 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*supervisor(void *arr)
{
	int		time_to_die;
	t_philo	*philo;

	philo = (t_philo*)arr;
	time_to_die = philo->time_to_die;
	while (time_to_die > 0)
	{
		time_to_die = time_to_die - 1;
		pthread_mutex_lock(&(philo->death_mutex));
		if (g_death_trigger[philo->philo_num] == 1)
		{
			g_death_trigger[philo->philo_num] = 0;
			time_to_die = philo->time_to_die;
		}
		pthread_mutex_unlock(&(philo->death_mutex));
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
		pthread_mutex_lock(philo->left_fork);
		print_state(" has taken a fork\n", philo->philo_num);
		pthread_mutex_lock(philo->right_fork);
		print_state(" has taken a fork\n", philo->philo_num);
		pthread_mutex_lock(&(philo->death_mutex));
		g_death_trigger[philo->philo_num] = 1;
		pthread_mutex_unlock(&(philo->death_mutex));
		print_state(" is eating\n", philo->philo_num);
		msleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
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
	gettimeofday(&g_time, NULL);
	g_death = 0;
	params = NULL;
	if (args_check(&params, argc, argv) == 1)
		return (0);
	if (philo_init(&philos, params, argc) == 1 || mutex_init(&philos) == 1
	|| supervisor_init(&philos) == 1 || threads_init(&philos) == 1)
		return (1);
	while (check_death(philos))
	{
		if (g_death == 1)
			break ;
	}
	return (0);
}

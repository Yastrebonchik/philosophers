/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:43:03 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/04 22:52:16 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			mutex_destroy(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < ((*philos)[0].philo_quan))
		pthread_mutex_destroy((*philos)[i++].left_fork);
}

void			threads_join(t_philo **philos)
{
	int	i;

	i = 0;
	while (i < ((*philos)[0].philo_quan))
	{
		pthread_join(*(*philos)[i].thread, NULL);
		pthread_join(*(*philos)[i].supervisor, NULL);
		i++;
	}
}

int				cycle_condition(t_philo *philo)
{
	if (philo->argc != 6)
		return (1);
	else
		return (philo->num_of_times_eat);
}

int				check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_quan)
	{
		if (g_death_trigger[i++] == 1)
			return (1);
	}
	return (0);
}

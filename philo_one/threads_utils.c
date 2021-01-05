/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:43:03 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/05 19:27:03 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			print_state(char *phrase, int phil_num)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&g_print_mutex);
	if (g_death != 1)
	{
		ft_putnbr_fd((tv.tv_sec - g_time.tv_sec) * 1000 +
		(tv.tv_usec - g_time.tv_usec) / 1000, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(phil_num, 1);
		ft_putstr_fd(phrase, 1);
	}
	pthread_mutex_unlock(&g_print_mutex);
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

	i = 1;
	while (i < philo->philo_quan + 1)
	{
		if (g_death_trigger[i] != 2)
			return (1);
		i++;
	}
	return (0);
}

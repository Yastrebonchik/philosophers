/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:40:50 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:58 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			print_state(char *phrase, int phil_num)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	sem_wait(g_print_semaphore);
	if (g_death != 1)
	{
		ft_putnbr_fd((tv.tv_sec - g_time.tv_sec) * 1000 +
		(tv.tv_usec - g_time.tv_usec) / 1000, 1);
		ft_putstr_fd("ms ", 1);
		ft_putnbr_fd(phil_num, 1);
		ft_putstr_fd(phrase, 1);
	}
	sem_post(g_print_semaphore);
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

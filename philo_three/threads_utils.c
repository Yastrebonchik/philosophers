/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:12:45 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:55 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			print_state(char *phrase, int phil_num)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	sem_wait(g_print_semaphore);
	ft_putnbr_fd((tv.tv_sec - g_time.tv_sec) * 1000 +
	(tv.tv_usec - g_time.tv_usec) / 1000, 1);
	ft_putstr_fd("ms ", 1);
	ft_putnbr_fd(phil_num, 1);
	ft_putstr_fd(phrase, 1);
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
	if (g_death_counter != philo->philo_quan)
		return (1);
	return (0);
}

void			parent_process(pid_t *pid, t_philo *philo)
{
	pid_t	wait_pid;
	int		exit_status;
	int		status;
	int		i;

	i = 0;
	while (check_death(philo))
	{
		wait_pid = waitpid(-1, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (exit_status == 2)
			g_death_counter++;
		else
			break ;
	}
	while (i < philo->philo_quan)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	exit(0);
}

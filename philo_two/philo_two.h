/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:30:09 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/05 22:03:49 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

#include <stdio.h>

typedef struct timeval	t_time;
typedef	unsigned int	t_mseconds;

typedef struct			s_philo
{
	int					philo_num;
	int					philo_quan;
	int					argc;
	int					num_of_times_eat;
	t_mseconds			time_to_die;
	t_mseconds			time_to_eat;
	t_mseconds			time_to_sleep;
	pthread_t			*supervisor;
	pthread_t			*thread;
}						t_philo;

int						g_death;
int						*g_death_trigger;
sem_t					*g_death_semaphore;
sem_t					*g_print_semaphore;
sem_t					*g_fork_semaphore;
t_time					g_time;

int						ft_atoi(const char *str);
int						check_death(t_philo *philo);
int						cycle_condition(t_philo *philo);
int						threads_join(t_philo **philos);
int						philo_init(t_philo **philos, int *params, int argc);
int						supervisor_init(t_philo **philos);
int						threads_init(t_philo **philos);
int						semaphore_init(t_philo **philos);
void					msleep(t_mseconds time);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *arr);
void					*philo(void *arr);
void					ft_putstr_fd(char *s, int fd);
void					print_state(char *phrase, int phil_num);

#endif
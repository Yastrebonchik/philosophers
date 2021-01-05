/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:28:27 by alexander         #+#    #+#             */
/*   Updated: 2021/01/05 16:38:26 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# include <stdio.h>

# define MALLOC_ERROR 1
# define GETTIMEOFDAY_ERROR 2
# define USLEEP_ERROR 3
# define PTHREAD_ERROR 4

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
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		death_mutex;
}						t_philo;

int						*g_death_trigger;
int						*g_mutex_trigger;
t_time					g_time;
pthread_mutex_t			g_print_mutex;

int						ft_atoi(const char *str);
int						check_death(t_philo *philo);
int						msleep(t_mseconds time);
int						cycle_condition(t_philo *philo);
void					errors_handling(int	err_num);
void					mutex_init(t_philo **array);
void					mutex_destroy(t_philo **array);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *arr);
void					*philo(void *arr);
void					supervisor_init(t_philo **philos);
void					threads_init(t_philo **philos);
void					threads_join(t_philo **philos);
void					ft_putstr_fd(char *s, int fd);
void					set_eat_trigger(t_philo *philos, int i);
void					print_state(char *phrase, int phil_num);
void					philo_init(t_philo **philos, int *params, int argc);

#endif

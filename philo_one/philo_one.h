/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:28:27 by alexander         #+#    #+#             */
/*   Updated: 2021/01/03 23:18:18 by yastrebon        ###   ########.fr       */
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

typedef struct timeval  t_time;
typedef	unsigned int	t_mseconds;

typedef struct		s_philo
{
	int				philo_num;
	int				philo_quan;
	t_mseconds		time_to_die;
	t_mseconds		time_to_eat;
	t_mseconds		time_to_sleep;
	int				num_of_times_eat;
	pthread_t		*supervisor;
	pthread_t		*thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				left_fork_trigger;
	int				right_fork_trigger;
}					t_philo;

t_time          g_time;
int             *g_death_trigger;
int				*g_mutex_trigger;

int				my_usleep(t_mseconds time);
int				ft_atoi(const char *str);
int				eat_trigger(t_philo *philos);
void			mutex_init(t_philo **array);
void			mutex_destroy(t_philo **array);
void			ft_putnbr_fd(int n, int fd);
void			*supervisor(void *arr);
void			*philo(void *arr);
void			supervisor_init(t_philo **philos);
void			threads_init(t_philo **philos);
void			threads_join(t_philo **philos);
void			ft_putstr_fd(char *s, int fd);
void			print_state(char *phrase, int phil_num);
void			philo_init(t_philo **philos, int *params, int argc);
unsigned int	ft_abs_substract(int a, int b);

#endif
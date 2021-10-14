/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:28:27 by alexander         #+#    #+#             */
/*   Updated: 2021/01/06 23:42:51 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

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

int						g_death;
int						*g_death_trigger;
t_time					g_time;
pthread_mutex_t			g_print_mutex;

int						ft_atoi(const char *str);
int						check_death(t_philo *philo);
int						cycle_condition(t_philo *philo);
int						threads_join(t_philo **philos);
int						philo_init(t_philo **philos, int *params, int argc);
int						supervisor_init(t_philo **philos);
int						threads_init(t_philo **philos);
int						mutex_init(t_philo **philos);
int						args_check(int **params, int argc, char **argv);
void					msleep(t_mseconds time);
void					mutex_destroy(t_philo **array);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *arr);
void					*philo(void *arr);
void					ft_putstr_fd(char *s, int fd);
void					print_state(char *phrase, int phil_num);

#endif

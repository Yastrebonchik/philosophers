/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:09:57 by kcedra            #+#    #+#             */
/*   Updated: 2021/01/06 23:42:54 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>
# include <semaphore.h>
# include <errno.h>
# include <stdio.h>

typedef struct timeval	t_time;
typedef	unsigned int	t_mseconds;

typedef struct			s_philo
{
	int					philo_num;
	int					philo_quan;
	int					argc;
	int					num_of_times_eat;
	int					death_trigger;
	t_mseconds			time_to_die;
	t_mseconds			time_to_eat;
	t_mseconds			time_to_sleep;
	pthread_t			supervisor;
}						t_philo;

int						g_death_counter;
sem_t					*g_death_semaphore;
sem_t					*g_print_semaphore;
sem_t					*g_fork_semaphore;
t_time					g_time;

int						ft_atoi(const char *str);
int						check_death(t_philo *philo);
int						cycle_condition(t_philo *philo);
int						threads_join(t_philo **philos);
int						philo_init(t_philo **philos, int *params, int argc);
int						process_init(t_philo **philos);
int						supervisor_init(t_philo **philos);
int						semaphore_init(t_philo **philos);
int						args_check(int **params, int argc, char **argv);
void					msleep(t_mseconds time);
void					parent_process(pid_t *pid, t_philo *philo);
void					ft_putnbr_fd(int n, int fd);
void					*supervisor(void *arr);
void					philo(void *arr);
void					ft_putstr_fd(char *s, int fd);
void					print_state(char *phrase, int phil_num);
size_t					ft_strlen(const char *s);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yastrebon <yastrebon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:28:27 by alexander         #+#    #+#             */
/*   Updated: 2021/01/01 23:37:18 by yastrebon        ###   ########.fr       */
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

pthread_mutex_t *g_mutex;
t_time          g_time;
int             g_counter;
int             g_trigger;

int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			print_state(char *phrase, int phil_num);
unsigned int	ft_abs_substract(int a, int b);

#endif
// void		clean_all(t_philo **philos)
// {
// 	int	i;
// 	int	philos_quan;

// 	i = 0;
// 	philos_quan = ((*philos)[0].philo_quan);
// 	mutex_destroy(philos);
// 	//while (i < ((*philos)[0].philo_quan))
// 	//	i++;
// 	free(*philos);
// }

// void			mutex_destroy(t_philo **philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ((*philos)[0].philo_quan))
// 	{
// 		pthread_mutex_destroy((*philos)[i].left_fork);
// 		pthread_mutex_destroy(&(*philos)[i].death_mutex);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&g_print_mutex);
// }
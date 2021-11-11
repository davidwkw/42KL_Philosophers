#include "philo.h"

void	*philo_parent_cycle(void *vars)
{
	t_args		*args;
	pthread_t	*threads;

	args = (t_args *)vars;
	create_philo_threads(&threads, args->conds->philo_num, &philo_cycle, args);
	while (!args->death && args->full != args->conds->philo_num)
		;
	pthread_detach(*args->philo_parent_thread);
	free(threads);
	return (NULL);
}
#include "philo.h"

/* 
** usleep necessary to ensure that index points to 
** the right philosopher in the thread before next iteration
*/
int	create_philo_threads(pthread_t **threads, int num, void *(*f)(void *), t_args *args)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * (num));
	if (!(*threads))
		return (1);
	i = -1;
	while (++i < num)
	{
		args->philo_i = i;
		if (pthread_create(&((*threads)[i]), NULL, f, (void *)args))
			return (1);
		usleep(30);
	}
	args->threads = *threads;
	return (0);
}

int	join_threads(pthread_t *threads, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
	}
	return (0);
}

int	detach_threads(pthread_t *threads, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_detach(threads[i]))
			return (1);
	}
	return (0);
}

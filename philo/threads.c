#include "philo.h"

int	create_threads(pthread_t **threads, int num)
{
	*threads = malloc(sizeof(pthread_t) * (num + 1));
	if (!(*threads))
		return (1);
	return (0);
}

int	create_philo_threads(pthread_t **threads, int num, void *(*f)(void *), t_args *args)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		args->philo_i = i;
		if (pthread_create(&((*threads)[i]), NULL, f, (void *)args))
			return (1);
		usleep(100);
	}
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

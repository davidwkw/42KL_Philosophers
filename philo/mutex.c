#include "philo.h"

int	create_mutexes(pthread_mutex_t **mutexes, int num, const pthread_mutexattr_t *attr)
{
	int	i;

	*mutexes = malloc(sizeof(pthread_mutex_t) * (num));
	if (!(*mutexes))
		return (1);
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&((*mutexes)[i]), attr))
			return (1);
	}
	return (0);
}

int	destroy_mutexes(pthread_mutex_t *mutexes, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_destroy(&mutexes[i]))
			return (1);
	}
	return (0);
}

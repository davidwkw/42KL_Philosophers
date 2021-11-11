#include "philo.h"

void	*death_monitor(void *vars)
{
	t_args	*args;
	int		i;

	args = (t_args *)vars;
	while (!args->death && args->full != args->conds->philo_num)
		;
	i = -1;
	while (++i < args->conds->philo_num)
		pthread_detach(args->threads[i]);
	return (NULL);
}
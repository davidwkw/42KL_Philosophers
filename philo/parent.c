#include "philo.h"

static int	check_death(t_args *args, t_philo *philo, unsigned long curr_time)
{
	long unsigned	death_time;

	death_time = philo->last_eat_time + args->conds->tt_die;
	if (curr_time >= death_time)
	{
		args->death = 1;
		return (1);
	}
	return (0);
}

void	*philo_parent_cycle(void *vars)
{
	t_args			*args;
	int				i;
	unsigned long	curr_time;

	args = (t_args *)vars;
	create_philo_threads(&args->threads, args->conds->philo_num, &philo_cycle, args);
	args->start = 1;
	usleep(args->conds->tt_die * 1000);
	while (!args->death && args->full < args->conds->philo_num)
	{
		i = -1;
		while (++i < args->conds->philo_num)
		{
			curr_time = get_time();
			if (check_death(args, &args->philos[i], curr_time) || (args->full == args->conds->philo_num))
			{
				pthread_mutex_lock(args->print_mutex);
				if (args->death)
					printf("%lu %d %s\n", curr_time, i + 1, "died");
				pthread_detach(args->philo_parent_thread);
				break;
			}
		}
	}
	return (NULL);
}

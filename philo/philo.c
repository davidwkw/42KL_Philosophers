#include "philo.h"

int	init_philos(t_philo **philos, int num)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * (num));
	if (!(*philos))
		return (1);
	i = -1;
	while (++i < num)
	{
		(*philos)[i].num = i + 1;
		if (!((i + 1) % 2))
		{
			(*philos)[i].fork_1 = (i + 1) % num;
			(*philos)[i].fork_2 = i % num;
		}
		else
		{
			(*philos)[i].fork_1 = i % num;
			(*philos)[i].fork_2 = (i + 1) % num;
		}
		(*philos)[i].last_eat_time = 0;
		(*philos)[i].eat_num = 0;
	}
	return (0);
}

void	*philo_cycle(void *vars)
{
	t_args			*args;
	t_philo			*philo;

	args = (t_args *)vars;
	philo = &args->philos[args->philo_i];
	while (!args->start)
		;
	print_status("is thinking", args->print_mutex, philo->num);
	if (!(philo->num % 2))
		usleep(500);
	philo->last_eat_time = get_time();
	while(!args->death && !(args->conds->max_eat_num >= 0 && philo->eat_num >= args->conds->max_eat_num))
	{
		eat_p(args, args->print_mutex, philo);
		sleep_p(args, args->print_mutex, philo);
		print_status("is thinking", args->print_mutex, philo->num);
		usleep(100);
	}
	return (NULL);
}

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

int	check_end_cond(t_args *args, t_philo *philo)
{
	long unsigned	curr_time;
	long unsigned	death_time;
	int				eat_cond;

	get_time(&curr_time);
	death_time = philo->last_eat_time + args->conds->tt_die;
	eat_cond = args->conds->max_eat_num >= 0 && philo->eat_num >= args->conds->max_eat_num;
	if (curr_time > death_time)
	{
		print_status("died", args->print_mutex, philo->num);
		args->death = 1;
	}
	return (args->death || eat_cond);
}

void	*philo_cycle(void *vars)
{
	t_args			*args;
	t_philo			philo;

	args = (t_args *)vars;
	philo = args->philos[args->philo_i];
	while (args->conds->philo_num != (args->philo_i + 1))
		;
	if (args->conds->philo_num == (args->philo_i + 1))
		usleep(25);
	print_status("is thinking", args->print_mutex, philo.num);
	get_time(&philo.last_eat_time);
	while (!check_end_cond(args, &philo))
	{
		take_fork_p(&args->fork_mutexes[philo.fork_1], args->print_mutex, &philo);
		take_fork_p(&args->fork_mutexes[philo.fork_2], args->print_mutex, &philo);
		eat_p(args, args->print_mutex, &philo);
		pthread_mutex_unlock(&args->fork_mutexes[philo.fork_1]);
		pthread_mutex_unlock(&args->fork_mutexes[philo.fork_2]);
		sleep_p(args, args->print_mutex, &philo);
		print_status("is thinking", args->print_mutex, philo.num);
	}
	return (NULL);
}

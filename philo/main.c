#include "philo.h"

static int	check_input(char **argv, char argc)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (!is_strdigit(argv[i]))
			return (1);
		if (ft_atoi(argv[i]) < 0)
			return (1);
	}
	return (0);
}

static int	init_cond(t_conditions *cond, int argc, char **argv)
{
	if (check_input(argv + 1, argc - 1))
		return (1);
	cond->philo_num = ft_atoi(argv[1]);
	cond->tt_die = ft_atoi(argv[2]);
	cond->tt_eat = ft_atoi(argv[3]);
	cond->tt_sleep = ft_atoi(argv[4]);
	cond->max_eat_num = -1;
	if (argc == 6)
		cond->max_eat_num = ft_atoi(argv[5]);
	return (0);
}

static void	init_args(t_args *args, t_conditions *conds, pthread_mutex_t *mutexes, pthread_mutex_t *p_mutex)
{
	args->conds = conds;
	args->fork_mutexes = mutexes;
	args->print_mutex = p_mutex;
	args->death = 0;
	args->full = 0;
}

static int	thread_handler(t_conditions *conds)
{
	pthread_t		*threads;
	pthread_t		death_thread;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*p_mutex;
	t_args			args;

	init_philos(&args.philos, conds->philo_num);
	create_mutexes(&mutexes, conds->philo_num, NULL);
	create_mutexes(&p_mutex, 1, NULL);
	init_args(&args, conds, mutexes, p_mutex);
	create_philo_threads(&threads, conds->philo_num, &philo_cycle, &args);
	pthread_create(&death_thread, NULL, &death_monitor ,&args);
	pthread_join(death_thread, NULL);
	join_threads(threads, conds->philo_num);
	destroy_mutexes(mutexes, conds->philo_num);
	pthread_mutex_destroy(p_mutex);
	free(mutexes);
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_conditions		conditions;
	
	if (argc != 5 && argc != 6)
		return (print_usage());
	if (init_cond(&conditions, argc, argv))
	{
		printf("Invalid input");
		return (1);
	}
	thread_handler(&conditions);
	return (0);
}

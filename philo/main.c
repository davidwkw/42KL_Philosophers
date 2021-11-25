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

static void	init_args(t_args *args, t_conditions *conds)
{
	args->conds = conds;
	args->start = 0;
	args->death = 0;
	args->full = 0;
}

static int	thread_handler(t_conditions *conds)
{
	t_args			args;

	init_philos(&args.philos, conds->philo_num);
	create_mutexes(&args.fork_mutexes, conds->philo_num, NULL);
	create_mutexes(&args.print_mutex, 1, NULL);
	init_args(&args, conds);
	pthread_create(&args.philo_parent_thread, NULL, &philo_parent_cycle, &args);
	pthread_join(args.philo_parent_thread, NULL);
	destroy_mutexes(args.fork_mutexes, conds->philo_num);
	destroy_mutexes(args.print_mutex, 1);
	free(args.fork_mutexes);
	free(args.print_mutex);
	free(args.threads);
	free(args.philos);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:44 by kwang             #+#    #+#             */
/*   Updated: 2024/01/08 01:54:00 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_input(char **argv, char argc)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if (!is_strdigit(argv[i]))
			return (1);
		if (ft_atoi(argv[i]) <= 0)
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

static int	thread_handler(t_args *args)
{
	create_philo_threads(&args->threads, args->conds.philo_num,
		&philo_cycle, args);
	death_monitor(args);
	join_threads(args->threads, args->conds.philo_num);
	return (0);
}

static int	init_args(t_args *args)
{
	int	ret;

	ret = 0;
	ret += init_philos(&args->philos, args->conds.philo_num, (void *)args);
	ret += create_mutexes(&args->fork_mutexes, args->conds.philo_num);
	ret += create_mutexes(&args->print_mutex, 1);
	ret += create_threads(&args->threads, args->conds.philo_num);
	ret += init_arg_mutexes(args);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_args	args;

	args = (t_args){};
	if (argc != 5 && argc != 6)
		return (print_usage());
	if (init_cond(&args.conds, argc, argv))
	{
		printf("Invalid input\n");
		return (EXIT_FAILURE);
	}
	if (!(init_args(&args)))
		thread_handler(&args);
	destroy_arg_mutexes(&args);
	free(args.threads);
	free(args.philos);
	free(args.fork_mutexes);
	free(args.print_mutex);
	return (EXIT_SUCCESS);
}

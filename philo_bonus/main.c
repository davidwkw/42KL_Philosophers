/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:32:46 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:32:48 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	init_args(t_args *args)
{
	int	ret;

	ret = 0;
	ret += init_philos(&args->philos, args->conds.philo_num, (void *)(args));
	args->child_pids = malloc(sizeof(pid_t) * args->conds.philo_num);
	if (!args->child_pids)
		ret++;
	return (ret);
}

void	process_handler(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->conds.philo_num)
	{
		args->child_pids[i] = fork();
		if (!args->child_pids[i])
			philo_handler(&args->philos[i]);
	}
	i = -1;
	while (++i < args->conds.philo_num)
		sem_post(args->start_sem);
	i = -1;
	while (++i < args->conds.philo_num)
		waitpid(args->child_pids[i], NULL, 0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	args = (t_args){};
	if (argc != 5 && argc != 6)
		return (print_usage());
	if (init_cond(&args.conds, argc, argv))
		error("Invalid input\n");
	init_sems(&args);
	if (!(init_args(&args)))
		process_handler(&args);
	close_semaphores(&args);
	unlink_semaphores();
	free(args.philos);
	free(args.child_pids);
	return (0);
}

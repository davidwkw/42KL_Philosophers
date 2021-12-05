/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:52 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:33:08 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_philo **philos, int num, void *args)
{
	int		i;

	*philos = malloc(sizeof(t_philo) * (num));
	if (!(*philos))
		return (1);
	i = -1;
	while (++i < num)
	{
		(*philos)[i].num = i + 1;
		(*philos)[i].last_eat_time = 0;
		(*philos)[i].eat_num = 0;
		(*philos)[i].full = 0;
		(*philos)[i].args = args;
	}
	return (0);
}

void	philo_handler(t_philo *philo, t_args *args)
{
	pthread_t	end_monitor;
	t_args		vars;

	vars = *(t_args *)philo->args;
	printf("philo %p\n", vars.start_sem);
	printf("args %p\n", args->start_sem);
	pthread_create(&end_monitor, NULL, &death_cycle, (void *)philo);
	pthread_detach(end_monitor);
	philo_process(philo, args);
	printf("exiting prematurely?\n");
	exit(0);
}

void	philo_process(t_philo *philo, t_args *args)
{
	printf("child start sem add %p\n", args->start_sem);
	sem_wait(args->start_sem);
	printf("starting...\n");
	args->start = 1;
	print_status("is thinking", philo, args);
	if (!(philo->num % 2))
		usleep(500);
	philo->last_eat_time = get_time();
	if (args->conds.philo_num == 1)
	{
		print_status("has taken a fork", philo, args);
		milisleep(args->conds.tt_die + 1);
		return ;
	}
	while(!philo->dead && !philo->full)
	{
		eat_p(args, philo);
		sleep_p(args, philo);
		print_status("is thinking", philo, args);
		usleep(100);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:52 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:54 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		(*philos)[i].args = args;
		(*philos)[i].full = 0;
	}
	return (0);
}

void	*philo_cycle(void *vars)
{
	t_args			*args;
	t_philo			*philo;

	philo = (t_philo *)vars;
	args = (t_args *)philo->args;
	while (!args->start)
		;
	print_status("is thinking", args->print_mutex, philo->num, args);
	if (!(philo->num % 2))
		usleep(500);
	philo->last_eat_time = get_time();
	if (args->conds.philo_num == 1)
	{
		print_status("has taken a fork", args->print_mutex, philo->num, args);
		usleep(args->conds.tt_die * 1000);
		print_status("died", args->print_mutex, philo->num, args);
		return (NULL);
	}
	while (!args->death && !philo->full)
	{
		eat_p(args, args->print_mutex, philo);
		sleep_p(args, args->print_mutex, philo);
		print_status("is thinking", args->print_mutex, philo->num, args);
		usleep(100);
	}
	return (NULL);
}

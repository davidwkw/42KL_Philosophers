/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:48 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:32:50 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_death(t_args *args, t_philo *philo, unsigned long curr_time)
{
	long unsigned	death_time;

	death_time = philo->last_eat_time + args->conds.tt_die;
	if (curr_time >= death_time)
		args->death = 1;
	return (args->death);
}

void	*death_cycle(void *vars)
{
	unsigned long	curr_time;
	t_philo			*philo;
	t_args			*args;

	philo = (t_philo *)vars;
	args = philo->args;
	while (!args->start)
		;
	usleep(args->conds.tt_die * 1000);
	while (!args->death && !philo->full)
	{
		curr_time = get_time();
		if (check_death(args, philo, curr_time))
		{
			sem_wait(args->print_sem);
			printf("%lu %d %s\n", curr_time, philo->num, "died");
			sem_post(args->end_sem);
		}
	}
	return (NULL);
}

void	*end_cycle(void *vars)
{
	t_args	*args;

	args = (t_args *)vars;
	sem_wait(args->end_sem);
	args->death = 1;
	sem_post(args->end_sem);
	return (NULL);
}

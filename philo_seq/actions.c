/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:41 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:43 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork_p(pthread_mutex_t *fork, pthread_mutex_t *p_mutex,
						t_philo *philo, t_args *args)
{
	pthread_mutex_lock(fork);
	print_status("has taken a fork", p_mutex, philo->num, args);
}

void	eat_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo)
{
	take_fork_p(&args->fork_mutexes[philo->fork_1],
		args->print_mutex, philo, args);
	take_fork_p(&args->fork_mutexes[philo->fork_2],
		args->print_mutex, philo, args);
	if (!(print_status("is eating", p_mutex, philo->num, args)))
	{
		philo->last_eat_time = get_time();
		if (args->conds.max_eat_num >= 0
			&& ++philo->eat_num == args->conds.max_eat_num)
		{
			philo->full = 1;
			args->all_full++;
		}
		milisleep(args->conds.tt_eat);
	}
	pthread_mutex_unlock(&args->fork_mutexes[philo->fork_1]);
	pthread_mutex_unlock(&args->fork_mutexes[philo->fork_2]);
}

void	sleep_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo)
{
	if (!(print_status("is sleeping", p_mutex, philo->num, args)))
		milisleep(args->conds.tt_sleep);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:41 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:32:45 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_fork_p(t_philo *philo, t_args *args)
{
	if (args->death)
		return ;
	sem_wait(args->fork_sem);
	print_status("has taken a fork", philo, args);
}

void	eat_p(t_args *args, t_philo *philo)
{
	int	max_eat;

	max_eat = args->conds.max_eat_num;
	if (args->death)
		return ;
	take_fork_p(philo, args);
	take_fork_p(philo, args);
	print_status("is eating", philo, args);
	philo->last_eat_time = get_time();
	if (args->conds.max_eat_num >= 0 && ++philo->eat_num == max_eat)
		philo->full = 1;
	milisleep(args->conds.tt_eat);
	sem_post(args->fork_sem);
	sem_post(args->fork_sem);
}

void	sleep_p(t_args *args, t_philo *philo)
{
	if (args->death)
		return ;
	print_status("is sleeping", philo, args);
	milisleep(args->conds.tt_sleep);
}

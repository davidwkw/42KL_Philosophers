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

void	philo_handler(t_philo *philo)
{
	pthread_t	end_monitor;
	pthread_t	death_monitor;

	pthread_create(&death_monitor, NULL, &death_cycle, (void *)philo);
	pthread_create(&end_monitor, NULL, &end_cycle, philo->args);
	pthread_detach(death_monitor);
	pthread_detach(end_monitor);
	philo_process(philo);
	exit(0);
}

void	philo_process(t_philo *philo)
{
	t_args	*args;

	args = philo->args;
	sem_wait(args->start_sem);
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
	while(!args->death && !philo->full)
	{
		eat_p(args, philo);
		sleep_p(args, philo);
		print_status("is thinking", philo, args);
		usleep(100);
	}
}

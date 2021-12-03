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
		(*philos)[i].args = args;
	}
	return (0);
}

void	philo_handler(t_philo *philo, t_args *args)
{
	pthread_t	end_monitor;

	pthread_create(&end_monitor, NULL, &end_cycle, (void *)philo);
	philo_process(philo, args);
	pthread_join(end_monitor, NULL);
}

void	philo_process(t_philo *philo, t_args *args)
{
	sem_wait(args->start_sem);
	args->start = 1;
	print_status("is thinking", philo->num, args);
	if (!(philo->num % 2))
		usleep(500);
	philo->last_eat_time = get_time();
	while(!args->death && !(args->conds.max_eat_num >= 0 && philo->eat_num >= args->conds.max_eat_num))
	{
		eat_p(args, philo);
		sleep_p(args, philo);
		print_status("is thinking", philo->num, args);
		usleep(100);
	}
}

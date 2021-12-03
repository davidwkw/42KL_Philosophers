/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:56 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:57 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_usage(void)
{
	printf("Usage: ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("Optional ([number_of_times_each_philosopher_must_eat])\n");
	return (1);
}

int	print_status(char *msg, int philo, t_args *args)
{
	if (args->death || args->full >= args->conds.philo_num)
		return (1);
	sem_wait(args->print_sem);
	printf("%lu %d %s\n", get_time(), philo, msg);
	sem_post(args->print_sem);
	return (0);
}
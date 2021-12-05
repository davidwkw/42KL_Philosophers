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

#include "philo.h"

int	print_usage(void)
{
	printf("Usage: ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("Optional ([number_of_times_each_philosopher_must_eat])\n");
	return (1);
}

int	print_status(char *msg, pthread_mutex_t *p_mutex, int philo, t_args *args)
{
	if (args->death)
		return (1);
	pthread_mutex_lock(p_mutex);
	printf("%lu %d %s\n", get_time(), philo, msg);
	pthread_mutex_unlock(p_mutex);
	return (0);
}

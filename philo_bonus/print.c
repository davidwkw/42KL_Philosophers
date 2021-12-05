/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:56 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:33:10 by kwang            ###   ########.fr       */
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

void	print_status(char *msg, t_philo *philo, t_args *args)
{
	if (philo->dead)
		return ;
	sem_wait(args->print_sem);
	printf("%lu %d %s\n", get_time(), philo->num, msg);
	sem_post(args->print_sem);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:50 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:51 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutexes(pthread_mutex_t **mutexes, int num)
{
	*mutexes = malloc(sizeof(pthread_mutex_t) * (num));
	if (!(*mutexes))
		return (1);
	return (0);
}

static int	init_mutexes(pthread_mutex_t **mutexes, int num, const pthread_mutexattr_t *attr)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&((*mutexes)[i]), attr))
			return (1);
	}
	return (0);
}

static int	destroy_mutexes(pthread_mutex_t *mutexes, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_destroy(&mutexes[i]))
			return (1);
	}
	return (0);
}

int	init_arg_mutexes(t_args *args)
{
	int	ret;

	ret = 0;
	if (init_mutexes(&args->fork_mutexes, args->conds.philo_num, NULL))
	{
		printf("Fork mutexes failed to be initialized\n");
		ret++;
	}
	if (init_mutexes(&args->print_mutex, 1, NULL))
	{
		printf("Print mutex failed to be initialized\n");
		ret++;
	}
	return (ret);
}

int	destroy_arg_mutexes(t_args *args)
{
	int	ret;

	ret = 0;
	if (destroy_mutexes(args->fork_mutexes, args->conds.philo_num))
	{
		printf("Fork mutexes failed to be destroyed\n");
		ret++;
	}
	pthread_mutex_unlock(args->print_mutex);
	if (destroy_mutexes(args->print_mutex, 1))
	{
		printf("Print mutex failed to be destroyed\n");
		ret++;
	}
	return (ret);
}

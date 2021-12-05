/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:33:11 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:33:13 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(FORK_SEM);
	sem_unlink(PRINT_SEM);
	sem_unlink(START_SEM);
	sem_unlink(END_SEM);
}

void	close_semaphores(t_args *args)
{
	sem_close(args->fork_sem);
	sem_close(args->print_sem);
	sem_close(args->start_sem);
	sem_close(args->end_sem);
}

void	init_sems(t_args *args)
{
	unlink_semaphores();
	args->fork_sem = sem_open(FORK_SEM, O_CREAT, S_IRUSR | S_IWUSR, args->conds.philo_num);
	args->print_sem = sem_open(PRINT_SEM, O_CREAT, S_IRUSR | S_IWUSR, 1);	
	args->start_sem = sem_open(START_SEM, O_CREAT, S_IRUSR | S_IWUSR, 0);
	args->end_sem = sem_open(END_SEM, O_CREAT, S_IRUSR | S_IWUSR, 0);
}

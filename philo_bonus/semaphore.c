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

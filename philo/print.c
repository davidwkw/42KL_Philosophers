#include "philo.h"

int	print_usage(void)
{
	printf("Usage: ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("Optional ([number_of_times_each_philosopher_must_eat])\n");
	return (1);
}

void	print_status(char *msg, pthread_mutex_t *p_mutex, int philo, t_args *args)
{
	while (args->death || args->full >= args->conds.philo_num)
		usleep(10000000);
	pthread_mutex_lock(p_mutex);
	printf("%lu %d %s\n", get_time(), philo, msg);
	pthread_mutex_unlock(p_mutex);
}
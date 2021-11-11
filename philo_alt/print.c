#include "philo.h"

int	print_usage(void)
{
	printf("Usage: ./philo [number_of_philosophers] ");
	printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
	printf("Optional ([number_of_times_each_philosopher_must_eat])\n");
	return (1);
}

void	print_status(char *msg, pthread_mutex_t *p_mutex, int philo)
{
	unsigned long	curr_time;

	pthread_mutex_lock(p_mutex);
	get_time(&curr_time);
	printf("%lu %d %s\n", curr_time, philo, msg);
	pthread_mutex_unlock(p_mutex);
}
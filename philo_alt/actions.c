#include "philo.h"

void	take_fork_p(pthread_mutex_t *fork, pthread_mutex_t *p_mutex, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_status("has taken a fork", p_mutex, philo->num);
}

void	eat_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo)
{
	print_status("is eating", p_mutex, philo->num);
	get_time(&philo->last_eat_time);
	philo->eat_num++;
	if (args->conds->max_eat_num >= 0 && philo->eat_num == args->conds->max_eat_num)
		args->full++;
	milisleep(args->conds->tt_eat);
}

void	sleep_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo)
{
	print_status("is sleeping", p_mutex, philo->num);
	milisleep(args->conds->tt_sleep);
}

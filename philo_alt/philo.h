#ifndef PHILO_H

// # define _GNU_SOURCE
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_conditions
{
	int	philo_num;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	max_eat_num;
}	t_conditions;

typedef struct s_philo
{
	int				num;
	int				fork_1;
	int				fork_2;
	unsigned long	last_eat_time;
	int				eat_num;
}	t_philo;

typedef struct s_args
{
	t_conditions	*conds;
	t_philo			*philos;
	int				philo_i;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*print_mutex;
	pthread_t		*philo_parent_thread;
	int				death;
	int				full;
}	t_args;

void	*philo_cycle(void *vars);
void	*philo_parent_cycle(void *vars);

int		create_philo_threads(pthread_t **threads, int num, void *(*f)(void *), t_args *args);
void	free_threads(pthread_t *threads, int size);
int		detach_threads(pthread_t *threads, int size);
int		join_threads(pthread_t *threads, int size);
int		destroy_mutexes(pthread_mutex_t *mutexes, int size);
int		create_mutexes(pthread_mutex_t **mutexes, int num, const pthread_mutexattr_t *attr);

int		init_philos(t_philo **philos, int num);

void	eat_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo);
void	take_fork_p(pthread_mutex_t *fork, pthread_mutex_t *p_mutex, t_philo *philo);
void	sleep_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo);

void	print_status(char *msg, pthread_mutex_t *p_mutex, int philo);
int		print_usage(void);

void	get_time(unsigned long *time);
void	milisleep(unsigned long duration);

int		ft_atoi(const char *str);
int		is_strdigit(char *str);

#endif

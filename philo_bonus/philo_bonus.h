#ifndef PHILO_BONUS_qH

# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

# define FORK_SEM "/fork_sem"
# define PRINT_SEM "/print_sem"
# define START_SEM "print_sem"
# define END_SEM "/end_sem"

typedef struct s_conditions
{
	int				philo_num;
	long unsigned	tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_eat_num;
}	t_conditions;

typedef struct s_philo
{
	int				num;
	unsigned long	last_eat_time;
	int				eat_num;
	void			*args;
}	t_philo;

typedef struct s_args
{
	t_conditions	conds;
	t_philo			*philos;
	pid_t			*child_pids;
	int				full;
	int				death;
	int				start;
	sem_t			*print_sem;
	sem_t			*fork_sem;
	sem_t			*start_sem;
	sem_t			*end_sem;
}	t_args;

void			*philo_cycle(void *vars);
void			unlink_semaphores(void);
void			close_semaphores(t_args *args);

void			*end_cycle(void *vars);
void			philo_handler(t_philo *philo, t_args *args);
void			philo_process(t_philo *philo, t_args *args);

int				init_philos(t_philo **philos, int num, void *args);

void			eat_p(t_args *args, t_philo *philo);
void			sleep_p(t_args *args, t_philo *philo);

int				print_status(char *msg, int philo, t_args *args);
int				print_usage(void);

unsigned long	get_time(void);
void			milisleep(unsigned long duration);

void			error(char *msg);
int				ft_atoi(const char *str);
int				is_strdigit(char *str);

#endif

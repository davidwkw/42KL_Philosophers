/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:32:58 by kwang             #+#    #+#             */
/*   Updated: 2021/12/05 10:33:04 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/wait.h>
# include <signal.h>

# define FORK_SEM "/fork_sem"
# define PRINT_SEM "/print_sem"
# define START_SEM "/start_sem"
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
	int				full;
	void			*args;
}	t_philo;

typedef struct s_args
{
	t_conditions	conds;
	int				death;
	t_philo			*philos;
	pid_t			*child_pids;
	int				start;
	sem_t			*print_sem;
	sem_t			*fork_sem;
	sem_t			*start_sem;
	sem_t			*end_sem;
}	t_args;


void			*philo_cycle(void *vars);
void			init_sems(t_args *args);
void			unlink_semaphores(void);
void			close_semaphores(t_args *args);

int				init_philos(t_philo **philos, int num, void *args);
void			philo_handler(t_philo *philo);
void			philo_process(t_philo *philo);

void			*death_cycle(void *vars);
void			*end_cycle(void *vars);

void			eat_p(t_args *args, t_philo *philo);
void			sleep_p(t_args *args, t_philo *philo);

void			print_status(char *msg, t_philo *philo, t_args *args);
int				print_usage(void);

unsigned long	get_time(void);
void			milisleep(unsigned long duration);

void			error(char *msg);
int				ft_atoi(const char *str);
int				is_strdigit(char *str);

#endif

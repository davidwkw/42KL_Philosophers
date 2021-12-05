/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwang <kwang@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:05:54 by kwang             #+#    #+#             */
/*   Updated: 2021/12/02 15:05:56 by kwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_conditions
{
	int	philo_num;
	long unsigned	tt_die;
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
	void			*args;
	int				full;
}	t_philo;

typedef struct s_args
{
	t_conditions	conds;
	t_philo			*philos;
	int				philo_i;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*print_mutex;
	pthread_t		philo_parent_thread;
	pthread_t		*threads;
	unsigned int	start : 1;
	int				all_full;
	int				death;
}	t_args;

void			*philo_cycle(void *vars);
void			*death_cycle(void *vars);

int				create_threads(pthread_t **threads, int num);
int				create_philo_threads(pthread_t **threads, int num, void *(*f)(void *), t_args *args);
int				join_threads(pthread_t *threads, int size);

int				create_mutexes(pthread_mutex_t **mutexes, int num);
int				init_arg_mutexes(t_args *args);
int				destroy_arg_mutexes(t_args *args);

int				init_philos(t_philo **philos, int num, void *args);

void			eat_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo);
void			sleep_p(t_args *args, pthread_mutex_t *p_mutex, t_philo *philo);

void			print_status(char *msg, pthread_mutex_t *p_mutex, int philo, t_args *args);
int				print_usage(void);

unsigned long	get_time(void);
void			milisleep(unsigned long duration);

int				ft_atoi(const char *str);
int				is_strdigit(char *str);

#endif

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long			res;
	unsigned int	i;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (res * sign > 2147483647)
			return (-1);
		else if (res * sign < -2147483648)
			return (0);
	}
	return (res * sign);
}

int	is_strdigit(char *str)
{
	while (*str)
	{
		if (*str < '0' && *str > '9')
			return (0);
		str++;
	}
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	milisleep(unsigned long duration)
{
	unsigned long	init_time;

	init_time = get_time();
	while (get_time() - init_time < duration)
		usleep(1);
}

void	error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
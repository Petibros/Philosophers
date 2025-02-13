#include "philo.h"

int	detach_threads(char *msg, int end, int start, t_args *args)
{
	//rectify cause mutexes not freed when the pthread_create fails
	while (start < end)
	{
		if (pthread_detach(args->philos[i] != 0))
			return (putstr_err("Problem unlocking a mutex"));
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			return (putstr_err("Problem destroying a fork (mutex)"));
		++start;
	}
	return (putstr_err(msg));
}

int	putstr_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (-1);
}

int	error_miss_args(void)
{
	write(2, "Intended use :\n ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", 129);
	return (1);
}

void	invalid_format(void)
{
	write(2, "There should be at least 1 philosopher\n\
number_of_philosophers and [number_of_times_each_philosopher_must_eat] \
range from 0 to 4294967295\n\
time_to_die, time_to_eat and time_to_sleep range from 0 to 4294967\n", 204);
}

int	ft_free(t_args *args, void (*error)(void), int status)
{
	if (error)
		error();
	free(args);
	return (status);
}

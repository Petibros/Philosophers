/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_n_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:45 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/22 23:01:50 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	detach_threads(char *msg, int end, int start, t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&args->forks[start]);
		++i;
	}
	while (start < end)
	{
		pthread_detach(args->philosophers[start]);
		pthread_mutex_destroy(&args->philos[i].last_ate_mutex);
		++start;
	}
	pthread_mutex_destroy(&args->time_mutex);
	pthread_mutex_destroy(&args->write);
	pthread_mutex_destroy(&args->is_running);
	pthread_mutex_destroy(&args->times_eaten_mutex);
	free(args->philosophers);
	free(args->philos);
	free(args->forks);
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

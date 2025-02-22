/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:26:33 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/22 23:01:09 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_args *args)
{
	unsigned int	i;
	long			time;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_lock(&args->philos[i].last_ate_mutex);
		time = calc_time(args->philos[i].last_ate,
				args->philos[i].time, args->philos[i].time_mutex);
		pthread_mutex_unlock(&args->philos[i].last_ate_mutex);
		if (time >= args->time_to_die)
		{
			pthread_mutex_lock(&args->is_running);
			args->stop = true;
			pthread_mutex_unlock(&args->is_running);
			time = calc_time(*args->philos[i].time_start,
					args->philos[i].time, args->philos[i].time_mutex);
			pthread_mutex_lock(&args->write);
			printf("%ld ms : philo n°%u died\n", time, i + 1);
			pthread_mutex_unlock(&args->write);
			return (i);
		}
		++i;
	}
	return (-1);
}

int	check_n_eat(t_args *args)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&args->times_eaten_mutex);
	while (i < args->n_philo && args->philos[i].times_eaten >= args->n_eat)
	{
		pthread_mutex_unlock(&args->times_eaten_mutex);
		++i;
		pthread_mutex_lock(&args->times_eaten_mutex);
	}
	pthread_mutex_unlock(&args->times_eaten_mutex);
	if (i == args->n_philo)
	{
		pthread_mutex_lock(&args->is_running);
		args->stop = true;
		pthread_mutex_unlock(&args->is_running);
		pthread_mutex_lock(&args->write);
		printf("%ld ms : all the philosophers have eaten enough\n", calc_time
			(args->time_start,
				&args->time, &args->time_mutex));
		pthread_mutex_unlock(&args->write);
		return (i - 1);
	}
	return (-1);
}

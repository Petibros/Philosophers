/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:06 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/17 19:36:40 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fork_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[0]);
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u has taken a fork\n",
		calc_time(philo->time_start, &philo->time, &philo->time_mutex),
		philo->philo_id);
	pthread_mutex_unlock(philo->write);
}

static void	eat_routine(t_philo *philo)
{
	fork_routine(philo);
	pthread_mutex_lock(&philo->forks[1]);
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u is eating\n", calc_time(philo->time_start,
			&philo->time, &philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
	gettimeofday(&philo->last_ate, NULL);
	usleep(philo->time_to_eat * 1000);
	++philo->times_eaten;
	pthread_mutex_unlock(&philo->forks[0]);
	pthread_mutex_unlock(&philo->forks[1]);
}

static void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u is sleeping\n", calc_time(philo->time_start,
			&philo->time, &philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
	usleep(philo->time_to_sleep * 1000);
}

static void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u is thinking\n", calc_time(philo->time_start,
			&philo->time, &philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
}

void	*routine(void *ptr)
{
	t_philo			*philo;

	philo = ptr;
	while (*philo->stop == false)
	{
		if (*philo->stop == false)
			eat_routine(philo);
		if (*philo->stop == false)
			sleep_routine(philo);
		if (*philo->stop == false)
			think_routine(philo);
	}
	return (NULL);
}

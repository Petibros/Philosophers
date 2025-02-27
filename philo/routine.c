/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:06 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/28 00:41:38 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fork_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u has taken a fork\n",
		calc_time(*philo->time_start, philo->time, philo->time_mutex),
		philo->philo_id);
	pthread_mutex_unlock(philo->write);
	if (philo->forks[1] == philo->forks[0])
	{
		pthread_mutex_unlock(philo->forks[0]);
		return (-1);
	}
	pthread_mutex_lock(philo->forks[1]);
	return (0);
}

static void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u has taken a fork\n",
		calc_time(*philo->time_start, philo->time, philo->time_mutex),
		philo->philo_id);
	printf("%ld ms : philo n°%u is eating\n", calc_time(*philo->time_start,
			philo->time, philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
	pthread_mutex_lock(&philo->last_ate_mutex);
	gettimeofday(&philo->last_ate, NULL);
	pthread_mutex_unlock(&philo->last_ate_mutex);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->times_eaten_mutex);
	++philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_mutex);
}

static void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u is sleeping\n", calc_time(*philo->time_start,
			philo->time, philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
	usleep(philo->time_to_sleep * 1000);
}

static void	think_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->write);
	printf("%ld ms : philo n°%u is thinking\n", calc_time(*philo->time_start,
			philo->time, philo->time_mutex), philo->philo_id);
	pthread_mutex_unlock(philo->write);
}

void	*routine(void *ptr)
{
	t_philo			*philo;

	philo = ptr;
	while (is_running(philo->is_running, philo->stop) == false)
	{
		pthread_mutex_lock(philo->forks[0]);
		if (is_running(philo->is_running, philo->stop) == true)
		{
			pthread_mutex_unlock(philo->forks[0]);
			break ;
		}
		if (fork_routine(philo) == -1)
			break ;
		if (is_running(philo->is_running, philo->stop) == false)
			eat_routine(philo);
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		if (is_running(philo->is_running, philo->stop) == false)
			sleep_routine(philo);
		if (is_running(philo->is_running, philo->stop) == false)
			think_routine(philo);
		usleep(800);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:17:07 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/23 05:39:59 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	fork_routine(t_args *args)
{
	sem_wait(args->write);
	printf("%ld ms : philo n°%u has taken a fork\n",
		calc_time(args->time_start, &args->time, args->time_sem),
		args->philo_id);
	sem_post(args->write);
	if (args->n_philo == 1)
	{
		sem_post(args->forks);
		return (-1);
	}
	sem_wait(args->forks);
	return (0);
}

static void	eat_routine(t_args *args)
{
	sem_wait(args->write);
	printf("%ld ms : philo n°%u has taken a fork\n",
		calc_time(args->time_start, &args->time, args->time_sem),
		args->philo_id);
	sem_post(args->write);
	sem_wait(args->write);
	printf("%ld ms : philo n°%u is eating\n", calc_time(args->time_start,
			&args->time, args->time_sem), args->philo_id);
	sem_post(args->write);
	sem_wait(args->last_ate_sem);
	gettimeofday(&args->last_ate, NULL);
	sem_post(args->last_ate_sem);
	usleep(args->time_to_eat * 1000);
	sem_wait(args->times_eaten_sem);
	++args->times_eaten;
	sem_post(args->times_eaten_sem);
}

static void	sleep_routine(t_args *args)
{
	sem_wait(args->write);
	printf("%ld ms : philo n°%u is sleeping\n", calc_time(args->time_start,
			&args->time, args->time_sem), args->philo_id);
	sem_post(args->write);
	usleep(args->time_to_sleep * 1000);
}

static void	think_routine(t_args *args)
{
	sem_wait(args->write);
	printf("%ld ms : philo n°%u is thinking\n", calc_time(args->time_start,
			&args->time, args->time_sem), args->philo_id);
	sem_post(args->write);
}

int	routine(t_args *args)
{
	while (is_running(args->stop_sem, &args->stop) == true)
	{
		sem_wait(args->forks);
		if (is_running(args->stop_sem, &args->stop) == false)
		{
			sem_post(args->forks);
			break ;
		}
		if (fork_routine(args) == -1)
			break ;
		if (is_running(args->stop_sem, &args->stop) == true)
			eat_routine(args);
		sem_post(args->forks);
		sem_post(args->forks);
		if (is_running(args->stop_sem, &args->stop) == true)
			sleep_routine(args);
		if (is_running(args->stop_sem, &args->stop) == true)
			think_routine(args);
		usleep(800);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:16:58 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/23 21:40:43 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(sem_t *sem, bool *stop)
{
	bool	is_running;

	sem_wait(sem);
	if (*stop == false)
		is_running = true;
	else
		is_running = false;
	sem_post(sem);
	return (is_running);
}

void	*lock_sim(void *ptr)
{
	t_args	*args;

	args = ptr;
	sem_wait(args->stop_sim);
	sem_post(args->stop_sim);
	args->stop = true;
	return (NULL);
}

static int	check_eat(t_args *args)
{
	(void) args;
	return (0);
}

static int	check_death(t_args *args)
{
	unsigned int	i;
	long			time;

	i = 0;
	while (i < args->n_philo)
	{
		sem_wait(args->last_ate_sem);
		time = calc_time(args->last_ate,
				&args->time, args->time_sem);
		sem_post(args->last_ate_sem);
		if (time >= args->time_to_die)
		{
			sem_post(args->stop_sim);
			time = calc_time(args->time_start,
					&args->time, args->time_sem);
			sem_wait(args->write);
			printf("%ld ms : philo n°%u died\n", time, i + 1);
			sem_post(args->write);
			return (i);
		}
		++i;
	}
	return (-1);
}

void	*check(void *ptr)
{
	t_args	*args;

	args = ptr;
	while (is_running(args->stop_sem, &args->stop) == true)
	{
		sem_post(args->stop_sem);
		if (args->n_eat != -1)
		{
			if (check_eat(args) == -1)
				return (NULL);
		}
		if (check_death(args) == -1)
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}

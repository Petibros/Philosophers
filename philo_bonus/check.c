/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:16:58 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/27 23:58:31 by sacgarci         ###   ########.fr       */
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
	sem_wait(args->stop_sem);
	args->stop = true;
	sem_post(args->stop_sem);
	sem_post(args->eaten_enough);
	return (NULL);
}

static int	check_eat(t_args *args)
{
	int	status;

	status = -1;
	sem_wait(args->times_eaten_sem);
	if (args->times_eaten >= args->n_eat)
	{
		status = 0;
		sem_post(args->eaten_enough);
	}
	sem_post(args->times_eaten_sem);
	return (status);
}

static int	check_death(t_args *args)
{
	long			time;

	sem_wait(args->last_ate_sem);
	time = calc_time(args->last_ate,
			&args->time, args->time_sem);
	sem_post(args->last_ate_sem);
	if (time >= args->time_to_die)
	{
		sem_wait(args->stop_sem);
		args->stop = true;
		sem_post(args->stop_sem);
		sem_post(args->stop_sim);
		time = calc_time(args->time_start, &args->time, args->time_sem);
		sem_wait(args->write);
		printf("%ld ms : philo n°%u died\n", time, args->philo_id);
		sem_post(args->write);
		return (0);
	}
	return (-1);
}

void	*check(void *ptr)
{
	t_args	*args;
	int		do_check_eat;

	args = ptr;
	do_check_eat = 1;
	while (is_running(args->stop_sem, &args->stop) == true)
	{
		sem_post(args->stop_sem);
		if (args->n_eat != -1)
		{
			if (do_check_eat == 1 && check_eat(args) != -1)
				do_check_eat = 0;
		}
		if (check_death(args) != -1)
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}

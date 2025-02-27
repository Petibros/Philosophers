/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:53:11 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/27 22:52:28 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lock_main(void *ptr)
{
	t_args	*args;

	args = ptr;
	sem_wait(args->stop_sim);
	sem_post(args->stop_sim);
	sem_wait(args->stop_sem);
	args->stop = true;
	sem_post(args->stop_sem);
	return (NULL);
}

void	*check_eaten_enough(void *ptr)
{
	t_args			*args;
	unsigned int	n;

	args = ptr;
	n = 0;
	while (n < args->n_philo)
	{
		sem_wait(args->eaten_enough);
		++n;
	}
	sem_wait(args->stop_sem);
	if (args->stop == false)
	{
		args->stop = true;
		sem_post(args->stop_sem);
		sem_post(args->stop_sim);
		sem_wait(args->write);
		printf("%ld ms : all philosophers have eaten enough\n",
			calc_time(args->time_start, &args->time, NULL));
		sem_post(args->write);
		return (NULL);
	}
	sem_post(args->stop_sem);
	return (NULL);
}

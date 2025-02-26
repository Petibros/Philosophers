/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:14:18 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/26 07:07:03 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sems_n_verif(t_args *args)
{
	args->time_sem = sem_open("philosphers_time", O_CREAT, S_IRWXU, 1);
	args->last_ate_sem = sem_open("philosophers_last_ate", O_CREAT, S_IRWXU, 1);
	args->stop_sem = sem_open("philosophers_stop", O_CREAT, S_IRWXU, 1);
	args->times_eaten_sem
		= sem_open("philosophers_times_eaten", O_CREAT, S_IRWXU, 1);
	sem_unlink("philosophers_time");
	sem_unlink("philosophers_times_eaten");
	sem_unlink("philosophers_last_ate");
	sem_unlink("philosophers_stop");
	if (pthread_create(&args->verif, NULL, &check, args))
	{
		destroy_n_join(args, false);
		return (-1);
	}
	if (pthread_create(&args->lock_to_stop, NULL, &lock_sim, args))
	{
		pthread_detach(args->verif);
		destroy_n_join(args, false);
		return (-1);
	}
	return (0);
}

void	destroy_n_join(t_args *args, bool join)
{
	if (join == true)
	{
		pthread_join(args->lock_to_stop, NULL);
		pthread_join(args->verif, NULL);
	}
	sem_close(args->time_sem);
	sem_close(args->last_ate_sem);
	sem_close(args->stop_sem);
	sem_close(args->times_eaten_sem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:38:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/23 05:40:09 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_args *args, unsigned int n, int status)
{
	int	pid;

	while (n < args->n_philo)
	{
		pid = fork();
		if (pid == -1)
			break ;
		if (pid == 0)
		{
			args->philo_id = n;
			if (init_sems_n_verif(args) == 0)
			{
				status = routine(args);
				destroy_n_join(args);
			}
			return (status);
		}
		++n;
	}
	return (status);
}

void	destroy_table(t_args *args)
{
	sem_close(args->forks);
	sem_close(args->write);
	sem_close(args->stop_sim);
	if (args->n_eat != -1)
		sem_close(args->times_eaten_sem);
}

void	init_table(t_args *args)
{
	args->stop = false;
	args->forks = sem_open("philosophers_forks", O_CREAT, 0777, args->n_philo);
	args->write = sem_open("philosophers_write", O_CREAT, 0777, 1);
	args->stop_sim = sem_open("philosophers_stop_sim", O_CREAT, 0777, 1);
	args->times_eaten_sem = NULL;
	if (args->n_eat != -1)
	{
		args->times_eaten_sem
			= sem_open("philosophers_times_eaten", O_CREAT, 0777, args->n_eat);
		sem_unlink("philosophers_times_eaten");
	}
	sem_unlink("philosophers_forks");
	sem_unlink("philosophers_write");
	sem_unlink("philosophers_stop_sim");
	gettimeofday(&args->time, NULL);
	gettimeofday(&args->last_ate, NULL);
	gettimeofday(&args->time_start, NULL);
	args->times_eaten = 0;
}

int	philosophers(t_args *args)
{
	unsigned int	n;
	int				status;

	n = 0;
	status = 0;
	init_table(args);
	printf("%ld\n", args->stop_sim->__align);
	printf("%ld\n", args->write->__align);
	printf("%ld\n", args->forks->__align);
	sem_wait(args->stop_sim);
	if (create_philos(args, n, status) == -1)
		status = -1;
	while (n < args->n_philo)
	{
		waitpid(-1, NULL, 0);
		++n;
	}
	destroy_table(args);
	return (status);
}

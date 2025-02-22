/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:38:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/21 04:57:45 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sems_n_verif(t_args *args)
{
	args->time_sem = sem_open("time", O_CREAT, S_IRWXU, 1);
	args->last_ate_sem = sem_open("last_ate", O_CREAT, S_IRWXU, 1);
	args->stop_sem = sem_open("stop", O_CREAT, S_IRWXU, 1);
	if (pthread_create(&args->verif, NULL, &check, args))
	{
		sem_close(args->time_sem);
		sem_close(args->last_ate_sem);
		sem_close(args->stop_sem);
		return (-1);
	}
	if (pthread_create(&args->lock_to_stop, NULL, &lock_sim, args))
	{
		sem_close(args->time_sem);
		sem_close(args->last_ate_sem);
		sem_close(args->stop_sem);
		return (-1);
	}
	return (0);
}

void	destroy_table(t_args *args)
{
	sem_close(args->forks);
	sem_close(args->write);
	sem_close(args->stop_sim);
	if (args->n_eat != -1)
		sem_close(args->times_eaten_sem);
}

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
				status = routine(args);
			return (status);
		}
		++n;
	}
	return (status);
}

void	init_table(t_args *args)
{
	args->stop = false;
	args->forks = sem_open("forks", O_CREAT, S_IRWXU, args->n_philo);
	args->write = sem_open("write", O_CREAT, S_IRWXU, 1);
	args->stop_sim = sem_open("stop", O_CREAT, S_IRWXU, 1);
	args->times_eaten_sem = NULL;
	if (args->n_eat != -1)
		args->times_eaten_sem
			= sem_open("n_eat", O_CREAT, S_IRWXU, args->n_eat);
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

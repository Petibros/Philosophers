/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:38:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/24 02:21:30 by sacgarci         ###   ########.fr       */
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
			args->philo_id = n + 1;
			if (init_sems_n_verif(args) == 0)
			{
				status = routine(args);
				destroy_n_join(args);
				sem_post(args->process_running);
				exit(0);
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
	sem_close(args->process_running);
	if (args->n_eat != -1)
	{
		sem_close(args->times_eaten_sem);
		free(args->times_eaten_sem);
	}
}

void	init_table(t_args *args)
{
	args->stop = false;
	args->forks = sem_open("forks", O_CREAT, 0777, args->n_philo);
	args->write = sem_open("write", O_CREAT, 0777, 1);
	args->stop_sim = sem_open("stop_sim", O_CREAT, 0777, 1);
	args->process_running = sem_open("process_running",
			O_CREAT, 0777, args->n_philo);
	args->times_eaten_sem = NULL;
	if (args->n_eat != -1)
		args->times_eaten_sem
			= sem_open("times_eaten", O_CREAT, 0777, args->n_eat);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("stop_sim");
	sem_unlink("process_running");
	if (args->n_eat != -1)
		sem_unlink("times_eaten");
	wait_process(args);
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
	wait_process(args);
	post_process(args);
	while (n < args->n_philo)
	{
		waitpid(-1, NULL, 0);
		++n;
	}
	destroy_table(args);
	return (status);
}

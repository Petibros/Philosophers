/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:38:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/26 08:13:46 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_table(t_args *args, bool join)
{
	if (join == true)
	{
		pthread_join(args->check_eaten_enough, NULL);
		pthread_join(args->lock_main, NULL);
	}
	sem_close(args->forks);
	sem_close(args->write);
	sem_close(args->stop_sim);
	sem_close(args->eaten_enough);
	sem_close(args->stop_main);
}

static int	init_table(t_args *args)
{
	args->stop = false;
	args->forks = sem_open("forks", O_CREAT, 0777, args->n_philo);
	args->write = sem_open("write", O_CREAT, 0777, 1);
	args->stop_sim = sem_open("stop_sim", O_CREAT, 0777, 0);
	args->eaten_enough = sem_open("eaten_enough", O_CREAT, 0777, 0);
	args->stop_main = sem_open("stop_main", O_CREAT, 0777, 1);
	sem_unlink("eaten_enough");
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("stop_sim");
	sem_unlink("stop_main");
	args->times_eaten = 0;
	if (pthread_create(&args->lock_main, NULL, &lock_main, args))
	{
		destroy_table(args, false);
		return (-1);
	}
	if (pthread_create(&args->check_eaten_enough,
			NULL, &check_eaten_enough, args))
	{
		destroy_table(args, false);
		pthread_detach(args->lock_main);
		return (-1);
	}
	return (0);
}

static int	create_philos(t_args *args, int pid, unsigned int n)
{
	gettimeofday(&args->time, NULL);
	gettimeofday(&args->last_ate, NULL);
	gettimeofday(&args->time_start, NULL);
	while (n < args->n_philo)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			args->philo_id = n + 1;
			if (init_sems_n_verif(args) == -1)
				return (-2);
			routine(args);
			destroy_n_join(args, true);
			return (1);
		}
		usleep(5000);
		++n;
	}
	return (0);
}

int	philosophers(t_args *args)
{
	long	status;

	if (init_table(args) == -1)
		return (-1);
	status = create_philos(args, 0, 0);
	if (status < 0)
	{
		sem_post(args->stop_sim);
		if (status == -1)
		{
			destroy_table(args, true);
			while (waitpid(-1, NULL, 0) > 0)
				continue ;
			return (-1);
		}
	}
	else if (status == 0)
	{
		pthread_join(args->check_eaten_enough, NULL);
		pthread_join(args->lock_main, NULL);
		while (waitpid(-1, NULL, 0) > 0)
			continue ;
	}
	destroy_table(args, false);
	return (status);
}

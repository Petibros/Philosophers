/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:38:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/25 08:20:32 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lock_main(void *ptr)
{
	t_args	*args;

	args = ptr;
	sem_wait(args->stop_sim);
	sem_post(args->stop_sim);
	sem_wait(args->stop_main);
	args->stop = true;
	sem_post(args->stop_main);
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
	sem_wait(args->stop_main);
	if (args->stop == false)
	{
		args->stop = true;
		sem_post(args->stop_main);
		sem_post(args->stop_sim);
		sem_wait(args->write);
		printf("%ld ms : all philosophers have eaten enough\n",
			calc_time(args->time_start, &args->time, args->stop_main));
		sem_post(args->write);
		return (NULL);
	}
	sem_post(args->stop_main);
	return (NULL);
}

static int	create_philos(t_args *args, int status)
{
	int				pid;
	unsigned int	n;

	n = 0;
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
				return (1);
			}
			return (status);
		}
		usleep(5000);
		++n;
	}
	return (status);
}

void	destroy_table(t_args *args)
{
	pthread_join(args->check_eaten_enough, NULL);
	pthread_join(args->lock_main, NULL);
	sem_close(args->forks);
	sem_close(args->write);
	sem_close(args->stop_sim);
	sem_close(args->eaten_enough);
	sem_close(args->stop_main);
}

static int	init_table(t_args *args)
{
	unsigned int	n;

	n = 0;
	args->stop = false;
	args->forks = sem_open("forks", O_CREAT, 0777, args->n_philo);
	args->write = sem_open("write", O_CREAT, 0777, 1);
	args->stop_sim = sem_open("stop_sim", O_CREAT, 0777, 1);
	args->eaten_enough = sem_open("eaten_enough", O_CREAT, 0777, args->n_philo);
	args->stop_main = sem_open("stop_main", O_CREAT, 0777, 1);
	sem_unlink("eaten_enough");
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("stop_sim");
	sem_unlink("stop_main");
	while (n < args->n_philo)
	{
		sem_wait(args->eaten_enough);
		++n;
	}
	sem_wait(args->stop_sim);
	gettimeofday(&args->time, NULL);
	gettimeofday(&args->last_ate, NULL);
	gettimeofday(&args->time_start, NULL);
	args->times_eaten = 0;
	if (pthread_create(&args->lock_main, NULL, &lock_main, args))
		return (-1);
	if (pthread_create(&args->check_eaten_enough,
			NULL, &check_eaten_enough, args))
		return (-1);
	return (0);
}

int	philosophers(t_args *args)
{
	int				status;

	status = 0;
	init_table(args);
	status = create_philos(args, status);
	while (status == 0 && waitpid(-1, NULL, 0) > 0)
		continue ;
	destroy_table(args);
	return (status);
}

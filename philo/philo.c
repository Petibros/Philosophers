/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:09 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/17 01:38:37 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_args *args, unsigned int i)
{
	args->philos[i].philo_id = i + 1;
	args->philos[i].time_to_eat = args->time_to_eat;
	args->philos[i].time_to_sleep = args->time_to_sleep;
	args->philos[i].forks[0] = args->forks[i];
	args->philos[i].forks[1] = args->forks[0];
	args->philos[i].times_eaten = 0;
	args->philos[i].stop = &args->stop;
	args->philos[i].write = &args->write;
	gettimeofday(&args->philos[i].time_start, NULL);
	args->philos[i].last_ate.tv_sec = args->philos[i].time_start.tv_sec;
	args->philos[i].last_ate.tv_usec = args->philos[i].time_start.tv_usec;
}

static void	table_gestion(t_args *args)
{
	unsigned int	i;
	long			n;

	i = 0;
	while (true)
	{
		usleep(1000);
		n = check_death(args);
		if (n != -1)
			return ;
		if (args->n_eat != -1)
			n = check_n_eat(args);
		if (n != -1)
			return ;
	}
}

static int	destroy_table(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(args->philosophers[i], NULL);
		++i;
	}
	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&args->write);
	return (0);
}

static int	init_table(t_args *args)
{
	unsigned int	i;

	i = 0;
	args->stop = false;
	pthread_mutex_init(&args->write, NULL);
	while (i < args->n_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		++i;
	}
	i = 0;
	while (i < args->n_philo)
	{
		init_philo(args, i);
		if (i < args->n_philo - 1)
			args->philos[i].forks[1] = args->forks[i + 1];
		pthread_create(&args->philosophers[i], NULL,
			&routine, &args->philos[i]);
		++i;
	}
	return (0);
}

int	philosophers(t_args *args)
{
	args->philosophers = malloc(args->n_philo * sizeof(pthread_t));
	if (!args->philosophers)
		return (putstr_err("Failed to alloc args->philosophers\n"));
	args->forks = malloc(args->n_philo * sizeof(pthread_mutex_t));
	if (!args->forks)
	{
		free(args->philosophers);
		return (putstr_err("Failed to alloc args->forks\n"));
	}
	args->philos = malloc(args->n_philo * sizeof(t_philo));
	if (!args->philos)
	{
		free(args->forks);
		free(args->philosophers);
		return (putstr_err("Failed to alloc args->philos\n"));
	}
	init_table(args);
	table_gestion(args);
	destroy_table(args);
	free(args->philosophers);
	free(args->philos);
	free(args->forks);
	return (0);
}

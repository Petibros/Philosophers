/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:09 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/15 17:08:07 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo			*philo;

	philo = ptr;
	philo->stop = false;
	gettimeofday(&philo->time_start, NULL);
	philo->last_ate.tv_sec = philo->time_start.tv_sec;
	philo->last_ate.tv_usec = philo->time_start.tv_usec;
	while (philo->stop == false)
	{
		pthread_mutex_lock(&philo->forks[0]);
		printf("%ld %u has taken a fork\n",
			calc_time(philo->time_start, &philo->time), philo->philo_id);
		pthread_mutex_lock(&philo->forks[1]);
		printf("%ld %u is eating\n", calc_time(philo->time_start, &philo->time), philo->philo_id);
		gettimeofday(&philo->last_ate, NULL);
		++philo->times_eaten;
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->forks[0]);
		pthread_mutex_unlock(&philo->forks[1]);
		printf("%ld %u is sleeping\n", calc_time(philo->time_start, &philo->time), philo->philo_id);
		usleep(philo->time_to_sleep * 1000);
		printf("%ld %u is thinking\n", calc_time(philo->time_start, &philo->time), philo->philo_id);
	}
	return (NULL);
}

static void	table_gestion(t_args *args)
{
	int	i;

	i = 0;
	while (true)
	{
		if (check_death(args) == 0 || (args->n_eat != -1 && check_n_eat(args) == 0))
			break ;
	}
	while (i < args->n_philo)
	{
		args->philos[i].stop = true;
		++i;
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
	return (0);
}

static int	init_table(t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		++i;
	}
	i = 0;
	while (i < args->n_philo)
	{
		args->philos[i].philo_id = i + 1;
		args->philos[i].time_to_eat = args->time_to_eat;
		args->philos[i].time_to_sleep = args->time_to_sleep;
		args->philos[i].forks[0] = args->forks[i];
		args->philos[i].forks[1] = args->forks[0];
		args->philos[i].times_eaten = 0;
		if (i < args->n_philo - 1)
			args->philos[i].forks[1] = args->forks[i + 1];
		pthread_create(&args->philosophers[i], NULL, &routine, &args->philos[i]);
		++i;
	}
	return (0);
}

int	philosophers(t_args *args)
{
	args->philosophers = malloc(args->n_philo * sizeof(pthread_t));
	if (!args->philos)
		return (putstr_err("Failed to alloc args->philos\n"));
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

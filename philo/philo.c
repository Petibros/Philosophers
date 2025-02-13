#include "philo.h"

void	routine(t_args *args)
{
	unsigned int	philo_id;

	philo_id = args->philo;
	pthread_mutex_unlock(&args->forks[philo_id - 1]);
	while (1)
	{
		
	}
}

static int	destroy_table(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			return (putstr_err("Problem destroying a fork (mutex)"));
		if (pthread_join(&args->philos[i], NULL) != 0)
			return (putstr_err("Problem joining a philosopher (thread)"));
		++i;
	}
	return (0);
}

static int	init_table(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (putstr_err("Problem initializing a fork (mutex)"));
		pthread_mutex_lock(&args->forks[i]);
		args->philo = i + 1;
		if (pthread_create(&args->philos[i], NULL, &routine, args) != 0)
			return (putstr_err("Problem creating a philosopher (thread)"));
		++i;
	}
	return (0);
}

int	philosophers(t_args *args)
{
	args->philos = malloc(args->n_philo * sizeof(pthread_t));
	if (!args->philos)
		return (putstr_err("Failed to alloc args->philos\n"));
	args->forks = malloc(args->n_philo * sizeof(pthread_mutex_t));
	if (!args->forks)
	{
		free(args->philos);
		return (putstr_err("Failed to alloc args->forks\n"));
	}
	if (init_table(args) == -1 || destroy_table(args) == -1)
	{
		free(args->philos);
		free(args->forks);
		return (-1);
	}
}

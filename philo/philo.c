#include "philo.h"

static int	loop(t_args *args, unsigned int philo_id, pthread_mutex_t forks[2])
{}

void	routine(t_args *args)
{
	unsigned int	philo_id;
	pthread_mutex_t	forks[2];

	philo_id = args->philo;
	if (pthread_mutex_unlock(&args->forks[philo_id - 1]) != 0)
		return (detach_threads("Problem unlocking a mutex",
				args->philo, start, args));
	forks[0] = philo_id - 1;
	if (philo_id == args->n_philo)
		forks[1] = 0;
	else
		forks[1] = forks[0] + 1;
	loop(args, philo_id, forks);
}

static int	destroy_table(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_destroy(&args->forks[i]) != 0)
			return (detach_threads("Problem destroying a fork (mutex)"));
		if (pthread_join(&args->philos[i], NULL) != 0)
			return (detach_threads("Problem joining a philosopher (thread)"
					, args->n_philo, i, args));
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
			return (detach_threads("Problem initializing a fork (mutex)"
					, i, 0, args));
		if (pthread_mutex_lock(&args->forks[i]) != 0)
			return (detach_threads("Problem locking a mutex", i, 0, args));
		args->philo = i + 1;
		if (pthread_create(&args->philos[i], NULL, &routine, args) != 0)
			return (detach_threads("Problem creating a philosopher (thread)"
					, i, 0, args));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:26:33 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/15 21:10:07 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		if (calc_time(args->philos[i].last_ate, &args->philos[i].time) >= args->time_to_die)
			return (0);
		++i;
	}
	return (-1);
}

int	check_n_eat(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo && args->philos[i].times_eaten >= args->n_eat)
		++i;
	if (i == args->n_philo)
		return (0);
	return (-1);
}

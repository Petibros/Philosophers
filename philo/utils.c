/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:26 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/18 22:27:35 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_running(pthread_mutex_t *is_running, bool *stop)
{
	bool	state;

	pthread_mutex_lock(is_running);
	state = *stop;
	pthread_mutex_unlock(is_running);
	return (state);
}

long	calc_time(struct timeval start, struct timeval *time,
		pthread_mutex_t *mutex_time)
{
	pthread_mutex_lock(mutex_time);
	gettimeofday(time, NULL);
	pthread_mutex_unlock(mutex_time);
	return ((time->tv_sec - start.tv_sec) * 1000
		+ (time->tv_usec - start.tv_usec) / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		++i;
	return (s1[i] - s2[i]);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

unsigned int	ft_atoui(char *nbr)
{
	unsigned int	n;
	int				i;

	i = 0;
	n = 0;
	while (nbr[i])
	{
		n = (n * 10) + (nbr[i] - 48);
		++i;
	}
	return (n);
}

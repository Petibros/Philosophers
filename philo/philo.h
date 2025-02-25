/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:09 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/24 21:49:48 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	bool			*stop;
	unsigned int	philo_id;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_eaten;
	struct timeval	last_ate;
	struct timeval	*time_start;
	struct timeval	*time;
	pthread_mutex_t	*time_mutex;
	pthread_mutex_t	last_ate_mutex;
	pthread_mutex_t	times_eaten_mutex;
	pthread_mutex_t	*write;
	pthread_mutex_t	*is_running;
	pthread_mutex_t	*forks[2];
}	t_philo;

typedef struct s_args
{
	bool			stop;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			n_eat;
	struct timeval	time_start;
	struct timeval	time;
	t_philo			*philos;
	pthread_t		*philosophers;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	is_running;
}	t_args;

bool			is_running(pthread_mutex_t *is_running, bool *stop);
void			invalid_format(void);
unsigned int	ft_atoui(char *nbr);
int				check_death(t_args *args);
int				check_n_eat(t_args *args);
long			calc_time(struct timeval start, struct timeval *time,
					pthread_mutex_t *mutex_time);
int				detach_threads(char *msg, int end, int start, t_args *args);
int				error_miss_args(void);
int				parsing(t_args *args, char **argv, int argc);
int				ft_free(t_args *args, void (*error)(void), int status);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *s);
int				philosophers(t_args *args);
int				putstr_err(char *msg);
void			*routine(void *ptr);

#endif

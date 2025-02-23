/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:09 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/23 04:19:43 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>

typedef struct s_args
{
	bool			stop;
	unsigned int	philo_id;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_eaten;
	struct timeval	time;
	struct timeval	time_start;
	struct timeval	last_ate;
	long			n_eat;
	pthread_t		verif;
	pthread_t		lock_to_stop;
	sem_t			*stop_sim;
	sem_t			*time_sem;
	sem_t			*last_ate_sem;
	sem_t			*stop_sem;
	sem_t			*write;
	sem_t			*times_eaten_sem;
	sem_t			*forks;
}	t_args;

int				init_sems_n_verif(t_args *args);
void			destroy_n_join(t_args *args);
void			*lock_sim(void *ptr);
void			*check(void *ptr);
long			calc_time(struct timeval start, struct timeval *time,
					sem_t *time_sem);
bool			is_running(sem_t *sem, bool *stop);
int				routine(t_args *args);
int				philosophers(t_args *args);
void			invalid_format(void);
unsigned int	ft_atoui(char *nbr);
int				parsing(t_args *args, char **argv, int argc);
int				error_miss_args(void);
int				ft_free(t_args *args, void (*error)(void), int status);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *s);

#endif

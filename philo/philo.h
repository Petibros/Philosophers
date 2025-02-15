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
	unsigned int	philo_id;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	times_eaten;
	struct timeval	last_ate;
	struct timeval	time_start;
	struct timeval	time;
	pthread_mutex_t	forks[2];
	bool			stop;
}	t_philo;

typedef struct s_args
{
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			n_eat;
	t_philo			*philos;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
}	t_args;

int				check_death(t_args *args);
int				check_n_eat(t_args *args);
long			calc_time(struct timeval start, struct timeval *time);
int				detach_threads(char *msg, int end, int start, t_args *args);
void			*routine(void *ptr);
int				error_miss_args(void);
int				parsing(t_args *args, char **argv, int argc);
int				ft_free(t_args *args, void (*error)(void), int status);
void			invalid_format(void);
int				ft_strcmp(char *s1, char *s2);
unsigned int	ft_atoui(char *nbr);
int				ft_strlen(char *s);
int				philosophers(t_args *args);
int				putstr_err(char *msg);

#endif

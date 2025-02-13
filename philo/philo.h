#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	unsigned int	philo;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			n_eat;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_args;

void			routine(t_args *args);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:09 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/19 22:16:08 by sacgarci         ###   ########.fr       */
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
# include <semaphore.h>

typedef struct s_args
{
	bool			stop;
	unsigned int	n_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			n_eat;
}	t_args;

void			invalid_format(void);
unsigned int	ft_atoui(char *nbr);
int				parsing(t_args *args, char **argv, int argc);
int				error_miss_args(void);
int				ft_free(t_args *args, void (*error)(void), int status);
int				ft_strcmp(char *s1, char *s2);
int				ft_strlen(char *s);

#endif

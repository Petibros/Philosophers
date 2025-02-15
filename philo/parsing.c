/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:37 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/14 20:31:49 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_argv(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (i > 1 && i < 5 && ft_strlen(av[i]) >= 7
			&& (ft_strlen(av[i]) > 7 || ft_strcmp(av[i], "4294967") > 0))
			return (-1);
		else if ((i == 1 || i == 5) && ft_strlen(av[i]) >= 10
			&& (ft_strlen(av[i]) > 10 || ft_strcmp(av[i], "4294967295") > 0))
			return (-1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
			++j;
		}
		++i;
	}
	if (ft_atoui(av[1]) < 1)
		return (-1);
	return (1);
}

int	parsing(t_args *args, char **argv, int argc)
{
	int				i;
	unsigned int	*n;

	i = 1;
	if (check_argv(argv, argc) == -1)
		return (-1);
	if (argc == 5)
		args->n_eat = -1;
	while (i < argc)
	{
		if (i == 1)
			n = &args->n_philo;
		else if (i == 2)
			n = &args->time_to_die;
		else if (i == 3)
			n = &args->time_to_eat;
		else if (i == 4)
			n = &args->time_to_sleep;
		else if (i == 5)
			n = (unsigned int *)&args->n_eat;
		*n = ft_atoui(argv[i]);
		++i;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:31:41 by sacgarci          #+#    #+#             */
/*   Updated: 2025/02/26 07:34:27 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 5 && argc != 6)
		return (error_miss_args());
	args = malloc(sizeof(t_args));
	if (!args)
	{
		write(2, "Failed to alloc args\n", 21);
		return (1);
	}
	if (parsing(args, argv, argc) == -1)
		return (ft_free(args, &invalid_format, 1));
	if (philosophers(args) <= -1)
		return (ft_free(args, NULL, 1));
	return (ft_free(args, NULL, 0));
}

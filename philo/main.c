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
	if (philo(args) == -1)
		return (ft_free(args, NULL, 1));
	return (ft_free(args, NULL, 0));
}

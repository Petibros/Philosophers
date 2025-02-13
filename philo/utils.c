#include "philo.h"

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

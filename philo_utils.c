#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return (1);
	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (1);
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}

unsigned long	ft_atou(const char *str)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = -1;
	while (str[++i] && str[i] >= 48 && str[i] <= 57)
		result = result * 10 + str[i] - 48;
	return (result);
}

int	ft_error_arguments(void)
{
	printf("Bad arguments number. Type:\n");
	printf("    %sarg1:%s number of philosophers.\n", CYAN, NC);
	printf("    %sarg2:%s time to survive without eating (in milisec).\n", CYAN, NC);
	printf("    %sarg3:%s timme eating (in milisec).\n", CYAN, NC);
	printf("    %sarg4:%s time sleeping (in milisec).\n", CYAN, NC);
	printf("    %sarg5:%s The program will stop if all philosophers eat this number (OPTIONAL).\n", CYAN, NC);
	return (1);
}

int	check_arguments(int c, char **v)
{
	int i;

	if (c != 5 && c!= 6)
		return (0);
	i = 0;
	while (++i < c)
		if (ft_atou(v[i]) == 0 && ft_strcmp(v[i], "0") != 0)
			return (0);
	return (ft_atou(v[1]));
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); 
}

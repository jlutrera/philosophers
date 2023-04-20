#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define NC 	"\e[0m"
# define YELLOW "\e[33m"
# define RED 	"\e[31m"
# define GREEN 	"\e[32m"
# define CYAN	"\e[36m"

typedef struct
{
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	n_times_eat;
}	t_data;

typedef struct
{
	int				id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t *fork_right;
	t_data			data_time;
}	t_philo;

int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_atou(const char *str);
int				ft_error_arguments(void);
int				check_arguments(int c, char **v);
unsigned long	ft_get_time(void);
#endif
#include "philo.h"

void	ft_clean_memory(pthread_t *philos, pthread_mutex_t *forks, t_philo *philos_data, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_destroy(&forks[i]);
	free(philos);
	free(forks);
	free(philos_data);
}

void	ft_print_message(char *s, unsigned long lap, int id, unsigned long i)
{
	unsigned long	now;

	id++;
	now = ft_get_time() - lap;
	if (ft_strcmp(" ...............is eating 🍝", s) == 0)
		printf("[%s%04li%s][%s%d%s] %s (%s%ld%s).\n", YELLOW, now, NC, GREEN, id, NC, s, YELLOW, i, NC);
	else
		printf("[%s%04li%s][%s%d%s] %s", YELLOW, now, NC, GREEN, id, NC, s);
}

void	*table(void *arg)
{
 	t_philo 		*phi;
	unsigned long	i;
	unsigned long	hungry;
	unsigned long	origin;

	phi = (t_philo *)arg;
	i = 0;
	origin = phi->data_time.t_init;
	hungry = origin;
	while (++i <= phi->data_time.n_times_eat)
	{
		pthread_mutex_lock(phi->fork_left);
		if ((ft_get_time() - hungry) >= phi->data_time.t_die)
		{
			ft_print_message(" .................is dead 💀\n", origin, phi->id, i);
			break;
		}	
		ft_print_message(" has taken the fork  left 🍴\n", origin, phi->id, i);
		if (phi->fork_left != phi->fork_right)
	        pthread_mutex_lock(phi->fork_right);
		else
			usleep(phi->data_time.t_die * 1000);
		if ((ft_get_time() - hungry) >= phi->data_time.t_die)
		{
			ft_print_message(" .................is dead 💀\n", origin, phi->id, i);
			break;
		}
		ft_print_message(" has taken the fork right 🍴\n", origin, phi->id, i);
        ft_print_message(" ...............is eating 🍝", origin, phi->id, i);
        usleep(phi->data_time.t_eat * 1000);
        hungry = ft_get_time();
		pthread_mutex_unlock(phi->fork_right);
        pthread_mutex_unlock(phi->fork_left);
    	ft_print_message(" .............is sleeping 🌙\n", origin, phi->id, i);
        usleep(phi->data_time.t_sleep * 1000);
		ft_print_message(" .............is thinking 💭\n", origin, phi->id, i);
	}
	return (NULL);
}

void	ft_init_data(int c, char **v, t_philo **philos_data, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		(*philos_data)[i].data_time.t_die = ft_atou(v[2]);
		(*philos_data)[i].data_time.t_eat = ft_atou(v[3]);
		(*philos_data)[i].data_time.t_sleep = ft_atou(v[4]);
		if (c == 6)
			(*philos_data)[i].data_time.n_times_eat = ft_atou(v[5]);
		else
			(*philos_data)[i].data_time.n_times_eat = ULONG_MAX;
	}
}

void	ft_init_mutex(pthread_mutex_t *f, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_mutex_init(&f[i], NULL);
}

void	ft_init_threads(t_philo *philos_data, pthread_mutex_t *forks, pthread_t *philos, int n)
{
	int				i;
	unsigned long	origin;
	void 			*status;

	i = -1;
	origin = ft_get_time();
	while (++i < n)
	{
		philos_data[i].id = i;
		philos_data[i].fork_left = &forks[i];
		philos_data[i].fork_right = &forks[(i + 1) % n];
		philos_data[i].data_time.t_init = origin;
		if (i % 2  != 0)
			usleep(1000);
		pthread_create(&philos[i], NULL, table, &philos_data[i]);
		pthread_join(philos[i], &status);
	}
}

int main(int argc, char **argv)
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	t_philo			*philos_data;
	int				n;

	n = check_arguments(argc, argv);
	if (n == 0)
		return (ft_error_arguments());
	philos_data = (t_philo *)malloc(n * sizeof(t_philo));
	ft_init_data(argc, argv, &philos_data, n);
	printf("****************************************************\n");
	printf("*                                                  *\n");
	printf("*   Philosophers begin to eat, sleep and think !   *\n");
	printf("*                                                  *\n");
	printf("****************************************************\n");
	philos = (pthread_t *)malloc(n * sizeof(pthread_t));
	forks = (pthread_mutex_t *)malloc(n * sizeof(pthread_mutex_t));
	if (!philos || !forks || !philos_data)
		return (1);
	ft_init_mutex(forks, n);
	ft_init_threads(philos_data, forks, philos, n);
	ft_clean_memory(philos, forks, philos_data, n);
	return (0);
} 

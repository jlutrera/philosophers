#include "philo.h"

void	ft_clean_memory(pthread_t *philos, pthread_mutex_t *forks, t_philo *philos_data, int n)
{
	int	i;
		
	i = -1;
	while (++i < n)
	{
		pthread_join(philos[i], NULL);
		pthread_mutex_destroy(&forks[i]);
	}
	free(philos);
	free(forks);
	free(philos_data);
}

void	ft_print_message(char *s, unsigned long t_lap, int id)
{
	printf("[%s%04li%s][%s%d%s] %s", YELLOW, t_lap, NC, GREEN, id + 1, NC, s);
}

void	*table(void *arg)
{
 	t_philo 		*phi;
	unsigned long	i;
	unsigned long	hungry;
	unsigned long	now;
	unsigned long	t_init;

	phi = (t_philo *)arg;
	i = 0;
	hungry = ft_get_time();
	t_init = hungry;
	while (++i <= phi->data_time.n_times_eat)
	{
		pthread_mutex_lock(phi->fork_left);
		now = ft_get_time();
		if ((now - hungry) > phi->data_time.t_die)
		{
			ft_print_message("is dead 💀\n", now - t_init, phi->id);
			exit(1);
		}	
		ft_print_message("has taken the fork left 🍴\n", now - t_init, phi->id);

        pthread_mutex_lock(phi->fork_right);
		now = ft_get_time();
		if ((now - hungry) > phi->data_time.t_die)
		{
			ft_print_message("is dead 💀\n", now - t_init, phi->id);
			exit(1);
		}
		ft_print_message("has taken the fork right 🍴\n", now - t_init, phi->id);
        ft_print_message("is eating 🍝", now - t_init, phi->id);
		printf("(%s%ld%s).\n", YELLOW, i, NC);
        usleep(phi->data_time.t_eat * 1000);
        hungry = ft_get_time();
		pthread_mutex_unlock(phi->fork_right);
        pthread_mutex_unlock(phi->fork_left);
    	ft_print_message("is sleeping 🌙\n", ft_get_time() - t_init, phi->id);
        usleep(phi->data_time.t_sleep * 1000);
		printf("[%s%04li%s][%s%d%s] is thinking 💭\n", YELLOW, ft_get_time() - t_init, NC, GREEN, phi->id + 1, NC);
	}
	exit(0);
}

void	ft_init_data(int c, char **v, t_philo **philos_data, int n)
{
	int	i;

	if (n == 1)
	{
		usleep(philos_data[0].data_time.t_die + 5);
		ft_print_message("died 💀\n", philos_data[0].data_time.t_die + 5, 0);
	}
	else
	{
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
	int	i;

	i = -1;
	while (++i < n)
	{
		philos_data[i].id = i;
		philos_data[i].fork_left = &forks[i];
		philos_data[i].fork_right = &forks[(i + 1) % n];
		if (i % 2  != 0)
			usleep(1000);
		pthread_create(&philos[i], NULL, table, &philos_data[i]);
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
	else
	{
		philos = (pthread_t *)malloc(n * sizeof(pthread_t));
		forks = (pthread_mutex_t *)malloc(n * sizeof(pthread_mutex_t));
		philos_data = (t_philo *)malloc(n * sizeof(t_philo));
		if (!philos || !forks || !philos_data)
			return (1);
		ft_init_mutex(forks, n);
		printf("[%s0000%s][%s·%s] Philosophers begin to eat, sleep and think !\n", YELLOW, NC, GREEN, NC);
		ft_init_data(argc, argv, &philos_data, n);
		ft_init_threads(philos_data, forks, philos, n);
		ft_clean_memory(philos, forks, philos_data, n);
	}
	return (0);
} 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:20:36 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:20:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_inc.h"

static void	ft_clean_memory(t_philo *phi, pthread_mutex_t *forks,
		pthread_t *philos, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.n)
		pthread_mutex_destroy(&forks[i]);
	pthread_mutex_destroy(&(param.writing));
	pthread_mutex_destroy(&(param.dc));
	free(philos);
	free(forks);
	free(phi);
}

static void	ft_init_param(int c, char **v, t_param *param)
{
	param->until_die = ft_atou(v[2]);
	param->eating = ft_atou(v[3]);
	param->sleeping = ft_atou(v[4]);
	if (c == 6)
		param->max_eaten = ft_atou(v[5]);
	else
		param->max_eaten = -1;
	param->someone_dead = 0;
	param->all_ate = 0;
}

static void	ft_init_philo(t_philo **philos, t_param *param,
		pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < param->n)
	{
		(*philos)[i].last_meal = 0;
		(*philos)[i].times_eaten = 0;
		(*philos)[i].id = i;
		(*philos)[i].fork_left = &forks[i];
		(*philos)[i].fork_right = &forks[(i + 1) % param->n];
		(*philos)[i].param = param;
	}
	i = -1;
	while (++i < param->n)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&(param->writing), NULL);
	pthread_mutex_init(&(param->dc), NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*phi;
	t_param			param;
	pthread_t		*philos;
	pthread_mutex_t	*forks;

	param.n = check_arguments(argc, argv);
	if (param.n == 0)
		return (ft_error_arguments());
	ft_init_param(argc, argv, &param);
	if (param.n == 1)
		return (message_one_philo(param.until_die));
	phi = (t_philo *)malloc(param.n * sizeof(t_philo));
	philos = (pthread_t *)malloc(param.n * sizeof(pthread_t));
	forks = (pthread_mutex_t *)malloc(param.n * sizeof(pthread_mutex_t));
	if (!philos || !forks || !phi)
		return (1);
	ft_init_philo(&phi, &param, forks);
	ft_print_table();
	ft_init_threads(phi, philos);
	ft_clean_memory(phi, forks, philos, param);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:20:36 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:20:36 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_arent_good(int c, char **v)
{
	int	i;

	if (c != 5 && c != 6)
		return (1);
	i = 0;
	while (++i < c)
		if (ft_atoi(v[i]) < 1)
			return (1);
	return (0);
}

static int	ft_init_param(int c, char **v, t_param *param)
{
	int	i;

	if (args_arent_good(c, v))
		return (1);
	param->n = ft_atoi(v[1]);
	param->until_die = ft_atoi(v[2]);
	if (param->n == 1)
		return (0);
	param->eating = ft_atoi(v[3]);
	param->sleeping = ft_atoi(v[4]);
	param->max_eaten = -1;
	if (c == 6)
		param->max_eaten = ft_atoi(v[5]);
	param->someone_dead = 0;
	param->all_ate = 0;
	param->forks = (pthread_mutex_t *)malloc(param->n
			* sizeof(pthread_mutex_t));
	if (!param->forks)
		return (1);
	i = -1;
	while (++i < param->n)
		pthread_mutex_init(&param->forks[i], NULL);
	pthread_mutex_init(&(param->writing), NULL);
	pthread_mutex_init(&(param->dc), NULL);
	return (0);
}

static int	ft_init_philo(t_philo **phi, t_param *param)
{
	int		i;
	t_philo	*p;

	p = (t_philo *)malloc(param->n * sizeof(t_philo));
	if (!p)
		return (1);
	i = -1;
	while (++i < param->n)
	{
		p[i].last_meal = 0;
		p[i].times_eaten = 0;
		p[i].id = i;
		p[i].fork_left = i;
		p[i].fork_right = (i + 1) % param->n;
		p[i].param = param;
	}
	*phi = p;
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*phi;
	t_param			param;

	phi = NULL;
	if (ft_init_param(argc, argv, &param))
		return (ft_error_arguments());
	if (param.n == 1)
		return (ft_one_philo(param.until_die));
	if (ft_init_philo(&phi, &param))
		return (1);
	return (ft_init_threads(phi));
}

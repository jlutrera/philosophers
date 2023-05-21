/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:20:36 by jutrera-          #+#    #+#             */
/*   Updated: 2023/05/13 20:07:41 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_arent_good(int c, char **v)
{
	int	i;

	i = 0;
	if (ft_strcmp(v[1], "-v") == 0)
		i = 1;
	if (c != 5 + i && c != 6 + i)
		return (4);
	while (++i < c)
		if (ft_atoi(v[i]) < 1)
			return (2);
	return (0);
}

static int	ft_init_mutex(t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->n)
		if (pthread_mutex_init(&param->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&(param->writing), NULL)
		|| pthread_mutex_init(&(param->dc), NULL))
		return (1);
	return (0);
}

static int	ft_init_param(int c, char **v, t_param *param)
{
	int	e;
	int	i;

	e = args_arent_good(c, v);
	if (e)
		return (e);
	i = (ft_strcmp(v[1], "-v") == 0);
	param->visual = i;
	param->n = ft_atoi(v[1 + i]);
	param->until_die = ft_atoi(v[2 + i]);
	if (param->n == 1)
		return (ft_manage_onephilo(*param));
	param->eating = ft_atoi(v[3 + i]);
	param->sleeping = ft_atoi(v[4 + i]);
	param->max_eaten = -1;
	if (c == 6 + i)
		param->max_eaten = ft_atoi(v[5 + i]);
	param->someone_dead = 0;
	param->all_ate = 0;
	param->forks = malloc(param->n * sizeof(pthread_mutex_t));
	if (!param->forks)
		return (3);
	return (ft_init_mutex(param));
}

static int	ft_init_philo(t_philo **phi, t_param *param)
{
	int		i;
	t_philo	*p;

	p = malloc(param->n * sizeof(t_philo));
	if (!p)
		return (3);
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
	t_philo	*phi;
	t_param	param;
	int		err;		

	phi = NULL;
	err = ft_init_param(argc, argv, &param);
	if (err)
		return (ft_error_arguments(err));
	err = ft_init_philo(&phi, &param);
	if (err)
		return (ft_error_arguments(err));
	err = ft_init_threads(phi);
	if (err)
		return (ft_error_arguments(err));
	return (0);
}

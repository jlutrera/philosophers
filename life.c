/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:34:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:34:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_clean_memory(t_philo *phi, t_param *param, pthread_t	*philos)
{
	int	i;

	i = -1;
	while (++i < param->n)
		pthread_mutex_destroy(&param->forks[i]);
	pthread_mutex_destroy(&(param->writing));
	pthread_mutex_destroy(&(param->dc));
	free(param->forks);
	free(phi);
	free(philos);
	return (0);
}

static int	ft_msg(char *s, t_param *param, t_philo *phi)
{
	unsigned long	now;

	pthread_mutex_lock(&(param->writing));
	if (!(param->someone_dead))
	{
		now = ft_get_time() - param->origin;
		printf("|%s%8li%s ", YELLOW, now, NC);
		printf("| %s%6d%s ", GREEN, phi->id + 1, NC);
		printf("| %s\n", s);
		if (ft_strcmp(F_R_MSG, s) == 0)
		{
			(phi->times_eaten)++;
			printf("|%s%8li%s ", YELLOW, now, NC);
			printf("| %s%6d%s ", GREEN, phi->id + 1, NC);
			printf("| %s %s%i%s\n", EATING, YELLOW, phi->times_eaten, NC);
		}
	}
	pthread_mutex_unlock(&(param->writing));
	return (ft_strcmp(DEAD_MSG, s) == 0);
}

static int	dead_checker(t_philo *phi, t_param *param)
{
	int	i;
	int	lap;

	while (!(param->all_ate))
	{
		i = -1;
		while (++i < param->n && !(param->someone_dead))
		{
			pthread_mutex_lock(&(param->dc));
			lap = (int)(ft_get_time() - phi[i].last_meal);
			if (lap > param->until_die)
				param->someone_dead = ft_msg(DEAD_MSG, param, &(phi[i]));
			pthread_mutex_unlock(&(param->dc));
		}
		if (param->someone_dead)
			break ;
		i = 0;
		while (param->max_eaten != -1 && i < param->n
			&& phi[i].times_eaten >= param->max_eaten)
			i++;
		if (i == param->n)
			param->all_ate = 1;
	}
	return (param->all_ate == 1);
}

static void	*life(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (!(phi->param->someone_dead))
	{
		ft_msg(THINK_MSG, phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_left]));
		ft_msg(F_L_MSG, phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_right]));
		ft_msg(F_R_MSG, phi->param, phi);
		phi->last_meal = ft_get_time();
		ft_msleep(phi->param->eating);
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_left]));
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_right]));
		if (phi->param->all_ate)
			break ;
		ft_msg(SLEEP_MSG, phi->param, phi);
		ft_msleep(phi->param->sleeping);
	}
	return ((void *)0);
}

int	ft_init_threads(t_philo *phi)
{
	int				i;
	int				status;
	t_param			*param;
	pthread_t		*philos;

	ft_print_head_table();
	param = phi[0].param;
	philos = (pthread_t *)malloc(param->n * sizeof(pthread_t));
	if (!philos)
		return (3);
	i = -1;
	param->origin = ft_get_time();
	while (++i < param->n)
	{
		if (pthread_create(&philos[i], NULL, life, &(phi[i])))
			return (6);
		phi[i].last_meal = param->origin;
		usleep(50);
	}
	status = dead_checker(phi, param);
	i = -1;
	while (++i < param->n)
		pthread_join(philos[i], NULL);
	ft_print_bottom_table(status, param->max_eaten);
	return (ft_clean_memory(phi, param, philos));
}

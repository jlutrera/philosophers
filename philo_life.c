/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:34:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:34:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_inc.h"

static void	ft_clean_memory(t_philo *phi, pthread_t *philos, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.n)
		pthread_mutex_destroy(&param.forks[i]);
	pthread_mutex_destroy(&(param.writing));
	pthread_mutex_destroy(&(param.dc));
	free(philos);
	free(param.forks);
	free(phi);
}

static void	ft_msleep(unsigned long time)
{
	unsigned long	i;

	i = ft_get_time();
	while (ft_get_time() - i < time)
		usleep(50);
}

static void	ft_msg(char *s, t_param *param, t_philo *phi)
{
	unsigned long	now;

	pthread_mutex_lock(&(param->writing));
	if (!(param->someone_dead))
	{
		now = ft_get_time() - param->origin;
		printf("|%s%8li%s ", YELLOW, now, NC);
		printf("| %s%6d%s ", GREEN, phi->id + 1, NC);
		printf("| %s\n", s);
		if (ft_strcmp("has taken the fork right 🍴 |", s) == 0)
		{
			(phi->times_eaten)++;
			printf("|%s%8li%s ", YELLOW, now, NC);
			printf("| %s%6d%s | is eating - ", GREEN, phi->id + 1, NC);
			printf("%s%3d%s          🍝 |\n", YELLOW, phi->times_eaten, NC);
		}
	}
	pthread_mutex_unlock(&(param->writing));
}

static int	dead_checker(t_philo *phi, t_param *param)
{
	int				i;

	while (!(param->all_ate))
	{
		i = -1;
		while (++i < param->n && !(param->someone_dead))
		{
			pthread_mutex_lock(&(param->dc));
			if (ft_get_time() - phi[i].last_meal >= param->until_die)
			{
				ft_msg("is dead                  💀 |", param, &(phi[i]));
				param->someone_dead = 1;
			}	
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
		ft_msg("is thinking              💭 |", phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_left]));
		ft_msg("has taken the fork left  🍴 |", phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_right]));
		ft_msg("has taken the fork right 🍴 |", phi->param, phi);
		phi->last_meal = ft_get_time();
		ft_msleep(phi->param->eating);
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_left]));
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_right]));
		if (phi->param->all_ate)
			break ;
		ft_msg("is sleeping              🌙 |", phi->param, phi);
		ft_msleep(phi->param->sleeping);
	}
	return (NULL);
}

int	ft_init_threads(t_philo *phi, pthread_t *philos)
{
	int				i;
	int				status;
	t_param			*param;
	pthread_t		*philos;

	philos = (pthread_t *)malloc(param.n * sizeof(pthread_t));
	if (!philos)
		return (1);
	i = -1;
	param = phi[0].param;
	param->origin = ft_get_time();
	while (++i < param->n)
	{
		if (pthread_create(&philos[i], NULL, life, &(phi[i])))
			return (1);
		phi[i].last_meal = param->origin;
		usleep(50);
	}
	status = dead_checker(phi, param);
	i = -1;
	while (++i < param->n)
		pthread_join(philos[i], NULL);
	ft_print_bottom_table(status, param->max_eaten);
	return (0);
}

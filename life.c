/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:34:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/05/17 18:17:37 by jutrera-         ###   ########.fr       */
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
	int				sd;

	pthread_mutex_lock(&(param->dc));
	sd = param->someone_dead;
	pthread_mutex_unlock(&(param->dc));
	if (!sd)
	{
		pthread_mutex_lock(&(param->writing));
		printf("|%s%8li%s ", YELLOW, ft_get_time() - param->origin, NC);
		printf("| %s%6d%s ", GREEN, phi->id + 1, NC);
		printf("| %s", s);
		if (ft_strcmp(EATING_MSG, s) == 0)
			printf(" %s%5i%s |\n", YELLOW, phi->times_eaten, NC);
		else
			printf("       |\n");
		pthread_mutex_unlock(&(param->writing));
	}
	return (!ft_strcmp(DEAD_MSG, s));
}

static int	checker(t_philo *phi, t_param *param)
{
	int	i;
	int	lap;

	while (!is_someone_dead(phi) && !is_all_eaten(phi))
	{
		i = -1;
		while (++i < param->n && !is_someone_dead(phi) && !is_all_eaten(phi))
		{
			pthread_mutex_lock(&(param->dc));
			lap = (int)(ft_get_time() - phi[i].last_meal);
			pthread_mutex_unlock(&(param->dc));
			if (lap > param->until_die)
			{
				ft_msg(DEAD_MSG, param, &(phi[i]));
				pthread_mutex_lock(&(param->dc));
				param->someone_dead = 1;
				pthread_mutex_unlock(&(param->dc));
			}
			check_all_eaten(phi);
		}
	}
	return (param->all_ate);
}

static void	*life(void *arg)
{
	t_philo	*phi;

	phi = arg;
	phi->last_meal = phi->param->origin;
	while (!is_someone_dead(phi))
	{
		ft_msg(THINK_MSG, phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_left]));
		ft_msg(F_L_MSG, phi->param, phi);
		pthread_mutex_lock(&(phi->param->forks[phi->fork_right]));
		ft_msg(F_R_MSG, phi->param, phi);
		ft_update(phi);
		ft_msg(EATING_MSG, phi->param, phi);
		ft_msleep(phi->param->eating);
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_left]));
		pthread_mutex_unlock(&(phi->param->forks[phi->fork_right]));
		if (is_all_eaten(phi))
			break ;
		ft_msg(SLEEP_MSG, phi->param, phi);
		ft_msleep(phi->param->sleeping);
	}
	return (NULL);
}

int	ft_init_threads(t_philo *phi)
{
	int				i;
	int				status;
	pthread_t		*philos;

	ft_print_head_table();
	philos = malloc(phi[0].param->n * sizeof(pthread_t));
	if (!philos)
		return (3);
	i = -1;
	phi[0].param->origin = ft_get_time();
	while (++i < phi[0].param->n)
	{
		pthread_create(&philos[i], NULL, life, &(phi[i]));
		usleep(50);
	}
	status = checker(phi, phi[0].param);
	i = -1;
	while (++i < phi[0].param->n)
		pthread_join(philos[i], NULL);
	ft_print_bottom_table(status, phi[0].param->max_eaten);
	return (ft_clean_memory(phi, phi[0].param, philos));
}

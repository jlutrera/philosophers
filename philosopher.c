/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:34:22 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:34:22 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(char *s, t_philo phi)
{
	unsigned long	now;
	int				n;

	if (!phi.param->someone_dead)
	{
		n = phi.id++;
		now = ft_get_time() - phi.param->origin;
		printf("[%s%04li%s][%s%d%s] %s", YELLOW, now, NC, GREEN, n, NC, s);
		if (ft_strcmp(" has taken the fork right 🍴\n", s) == 0)
		{
			phi.times_eaten++;
			printf("[%s%04li%s][%s%d%s] ...............is eating 🍝 (%s%d%s)\n",
				YELLOW, now, NC, GREEN, n, NC, YELLOW, phi.times_eaten, NC);
		}
	}
}

int	phi_is_dead(t_philo phi)
{
	if (phi.fork_left == phi.fork_right)
		usleep(phi.param->until_die * 1000);
	if (ft_get_time() - phi.last_meal < phi.param->until_die)
		return (0);
	if (phi.param->someone_dead == 0)
	{
		ft_print_message(" .................is dead 💀\n", phi);
		phi.param->someone_dead = 1;
	}
	return (1);
}

void	*philosopher(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (phi->times_eaten < phi->param->max_eaten
		&& !phi->param->someone_dead)
	{
		pthread_mutex_lock(phi->fork_left);
		if (phi_is_dead(*phi))
			break ;
		ft_print_message(" has taken the fork  left 🍴\n", *phi);
		pthread_mutex_lock(phi->fork_right);
		if (phi_is_dead(*phi))
			break ;
		ft_print_message(" has taken the fork right 🍴\n", *phi);
		usleep(phi->param->eating * 1000);
		phi->last_meal = ft_get_time();
		pthread_mutex_unlock(phi->fork_right);
		pthread_mutex_unlock(phi->fork_left);
		ft_print_message(" .............is sleeping 🌙\n", *phi);
		usleep(phi->param->sleeping * 1000);
		if (phi_is_dead(*phi))
			break ;
		ft_print_message(" .............is thinking 💭\n", *phi);
	}
	return (NULL);
}

void	ft_init_threads(t_philo *phi, pthread_t *philos)
{
	int	i;
	int	n;

	n = phi[0].param->n;
	i = -1;
	while (++i < n)
	{
		pthread_create(&philos[i], NULL, philosopher, &phi[i]);
		usleep(100);
	}
	i = -1;
	while (++i < n)
		pthread_join(philos[i], NULL);
}

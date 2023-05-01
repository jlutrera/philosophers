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

void	ft_print_message(char *s, t_philo *phi)
{
	unsigned long	now;

	pthread_mutex_lock(phi->writing);
	if (!phi->param->someone_dead)
	{	
		now = ft_get_time() - phi->param->origin;
		printf("|%s%8li%s | %s%6d%s | %s", YELLOW, now, NC,
			GREEN, phi->id + 1, NC, s);
		if (ft_strcmp("has taken the fork right 🍴 |\n", s) == 0)
		{
			phi->times_eaten++;
			printf("|%s%8li%s | %s%6d%s | is eating (%s%d%s)            🍝 |\n",
				YELLOW, now, NC, GREEN, phi->id + 1, NC,
				YELLOW, phi->times_eaten, NC);
		}
		if (ft_strcmp("is dead                  💀 |\n", s) == 0)
			phi->param->someone_dead = 1;
	}
	pthread_mutex_unlock(phi->writing);
}

int	phi_is_dead(t_philo *phi)
{
	if (phi->param->n == 1)
		usleep(phi->param->until_die * 1000);
	if (ft_get_time() - phi->last_meal >= phi->param->until_die)
		ft_print_message("is dead                  💀 |\n", phi);
	return (phi->param->someone_dead);
}

void	*ft_unlock_mutex(pthread_mutex_t *f_l, pthread_mutex_t *f_r)
{
	if (f_l)
		pthread_mutex_unlock(f_l);
	if (f_r)
		pthread_mutex_unlock(f_r);
	return ((void *)1);
}

void	*life(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (phi->times_eaten < phi->param->max_eaten
		&& !phi->param->someone_dead)
	{
		ft_print_message("is thinking              💭 |\n", phi);
		pthread_mutex_lock(phi->fork_left);
		ft_print_message("has taken the fork left  🍴 |\n", phi);
		if (phi_is_dead(phi))
			return (ft_unlock_mutex(phi->fork_left, NULL));
		pthread_mutex_lock(phi->fork_right);
		if (phi_is_dead(phi))
			return (ft_unlock_mutex(phi->fork_left, phi->fork_right));
		ft_print_message("has taken the fork right 🍴 |\n", phi);
		usleep(phi->param->eating * 1000);
		phi->last_meal = ft_get_time();
		ft_unlock_mutex(phi->fork_left, phi->fork_right);
		ft_print_message("is sleeping              🌙 |\n", phi);
		usleep(phi->param->sleeping * 1000);
		if (phi_is_dead(phi))
			return ((void *)1);
	}
	return ((void *)0);
}

int	ft_init_threads(t_philo *phi, pthread_t *philos)
{
	int	i;
	int	n;
	int	status;

	n = phi[0].param->n;
	i = -1;
	while (++i < n)
	{
		pthread_create(&philos[i], NULL, life, &phi[i]);
		usleep(100);
	}
	i = -1;
	while (++i < n)
		pthread_join(philos[i], (void *)&status);
	printf("\u2514---------\u2534--------");
	printf("\u2534-----------------------------\u2518\n");
	if (status == 0)
	{
		printf("\n       %sALL PHILOSOPHERS HAVE EATEN ", CYAN);
		printf("%s%i%s ", YELLOW, phi[0].param->max_eaten, CYAN);
		printf("TIMES ! %s\n\n", NC);
	}
	return (0);
}

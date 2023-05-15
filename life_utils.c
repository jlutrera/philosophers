/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:32:28 by jutrera-          #+#    #+#             */
/*   Updated: 2023/05/13 20:40:32 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_philo *phi)
{
	int	r;

	pthread_mutex_lock(&(phi->param->dc));
	r = phi->param->someone_dead;
	pthread_mutex_unlock(&(phi->param->dc));
	return (r);
}

int	check_all_eaten(t_philo *phi)
{
	int	i;

	pthread_mutex_lock(&(phi->param->dc));
	i = 0;
	while (phi->param->max_eaten != -1 && i < phi->param->n
		&& phi[i].times_eaten >= phi->param->max_eaten)
		i++;
	if (i == phi->param->n)
		phi->param->all_ate = 1;
	pthread_mutex_unlock(&(phi->param->dc));
	return (phi->param->all_ate == 1);
}

void	ft_update(t_philo *phi)
{
	pthread_mutex_lock(&(phi->param->dc));
	phi->last_meal = ft_get_time();
	phi->times_eaten++;
	pthread_mutex_unlock(&(phi->param->dc));
}

int	is_all_eaten(t_philo *phi)
{
	int	r;

	pthread_mutex_lock(&(phi->param->dc));
	r = phi->param->all_ate;
	pthread_mutex_unlock(&(phi->param->dc));
	return (r);
}

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

void	ft_clean_memory(t_philo *phi, pthread_mutex_t *forks, pthread_t *philos)
{
	int	i;
	int	n;

	i = -1;
	n = phi[0].param->n;
	while (++i < n)
		pthread_mutex_destroy(&forks[i]);
	free(philos);
	free(forks);
	free(phi);
}

void	ft_init_param(int c, char **v, t_param *param)
{
	param->until_die = ft_atou(v[2]);
	param->eating = ft_atou(v[3]);
	param->sleeping = ft_atou(v[4]);
	if (c == 6)
		param->max_eaten = ft_atou(v[5]);
	else
		param->max_eaten = INT_MAX;
	param->origin = ft_get_time();
	param->someone_dead = 0;
}

void	ft_init_philo(t_philo **phi, pthread_mutex_t *forks,
		pthread_mutex_t *message, t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->n)
	{
		(*phi)[i].last_meal = param->origin;
		(*phi)[i].times_eaten = 0;
		(*phi)[i].id = i;
		(*phi)[i].fork_left = &forks[i];
		if (param->n == 1)
			(*phi)[i].fork_right = NULL;
		else
			(*phi)[i].fork_right = &forks[(i + 1) % param->n];
		(*phi)[i].writing = message;
		(*phi)[i].param = param;
	}
	i = -1;
	while (++i < param->n)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(message, NULL);
}

static void	ft_print_table(void)
{
	printf("\n\n     %sPHILOSOPHERS BEGIN TO EAT, ", CYAN);
	printf("SLEEP & THINK !%s      \n", NC);
	printf("\u250c---------\u252c--------\u252c");
	printf("-----------------------------\u2510\n");
	printf("| Lap(ms) | Philo. |            Action           |\n");
	printf("\u251c---------\u253c--------\u253c");
	printf("-----------------------------\u2524\n");
}

int	main(int argc, char **argv)
{
	t_philo			*phi;
	t_param			param;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;

	param.n = check_arguments(argc, argv);
	if (param.n == 0)
		return (ft_error_arguments());
	phi = (t_philo *)malloc(param.n * sizeof(t_philo));
	philos = (pthread_t *)malloc(param.n * sizeof(pthread_t));
	forks = (pthread_mutex_t *)malloc(param.n * sizeof(pthread_mutex_t));
	if (!philos || !forks || !phi)
		return (1);
	ft_print_table();
	ft_init_param(argc, argv, &param);
	ft_init_philo(&phi, forks, &message, &param);
	ft_init_threads(phi, philos);
	ft_clean_memory(phi, forks, philos);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:31:50 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:31:50 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INC_H
# define PHILO_INC_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define NC 	"\e[0m"
# define YELLOW "\e[33m"
# define RED 	"\e[31m"
# define GREEN 	"\e[32m"
# define CYAN	"\e[36m"

typedef struct s_param
{
	int				n;
	int				someone_dead;
	int				max_eaten;
	int				all_ate;
	unsigned long	until_die;
	unsigned long	eating;
	unsigned long	sleeping;
	unsigned long	origin;
	pthread_mutex_t	writing;
	pthread_mutex_t	dc;
}	t_param;

typedef struct s_philo
{	
	int				id;
	int				times_eaten;
	unsigned long	last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_param			*param;
}	t_philo;

int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_atou(const char *str);
int				ft_error_arguments(void);
int				check_arguments(int c, char **v);
unsigned long	ft_get_time(void);
int				ft_init_threads(t_philo *phi, pthread_t *philos);
int				message_one_philo(unsigned long n);
void			ft_print_end_table(int status, int meals);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:31:50 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 10:31:50 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define NC 	"\033[0;0m"
# define YELLOW "\033[0;33m"
# define RED 	"\033[0;31m"
# define GREEN 	"\033[0;32m"
# define CYAN	"\033[0;36m"

# define DEAD_MSG	"is dead                  💀 |"
# define THINK_MSG	"is thinking              💭 |"
# define SLEEP_MSG	"is sleeping              🌙 |"
# define F_L_MSG	"has taken the fork left  🍴 |"
# define F_R_MSG	"has taken the fork right 🍴 |"

typedef struct s_param
{
	int				n;
	int				someone_dead;
	int				max_eaten;
	int				all_ate;
	int				until_die;
	int				eating;
	int				sleeping;
	unsigned long	origin;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	dc;
}	t_param;

typedef struct s_philo
{	
	int				id;
	int				times_eaten;
	unsigned long	last_meal;
	int				fork_left;
	int				fork_right;
	t_param			*param;
}	t_philo;

//************* utils.c *****************
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);
unsigned long	ft_get_time(void);
void			ft_msleep(unsigned long time);
//************* messages.c *******************
int				ft_error_arguments(void);
int				ft_one_philo(int n);
void			ft_print_bottom_table(int status, int meals);
void			ft_print_head_table(void);
//************* life.c ******************
int				ft_init_threads(t_philo *phi);

#endif

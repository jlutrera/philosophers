/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:00:56 by jutrera-          #+#    #+#             */
/*   Updated: 2023/04/28 11:00:56 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_inc.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return (1);
	i = -1;
	while (s1[++i])
		if (s1[i] != s2[i])
			return (1);
	if (s2[i] == '\0')
		return (0);
	else
		return (-1);
}

unsigned long	ft_atou(const char *str)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = -1;
	while (str[++i] && str[i] >= 48 && str[i] <= 57)
		result = result * 10 + str[i] - 48;
	return (result);
}

unsigned long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

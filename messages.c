/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:32:20 by jutrera-          #+#    #+#             */
/*   Updated: 2023/05/13 15:20:32 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_head_table(void)
{
	printf("\n\n       %sPHILOSOPHERS BEGIN TO EAT, ", CYAN);
	printf("SLEEP & THINK !%s      \n", NC);
	printf("\u250c---------\u252c--------\u252c");
	printf("-----------------------------\u252c-------\u2510\n");
	printf("| Lap(ms) | Philo. |            Action           | Meals |\n");
	printf("\u251c---------\u253c--------\u253c");
	printf("-----------------------------\u253c-------\u2524\n");
}

int	ft_error_arguments(int err)
{
	if (err == 1)
		printf("Mutex error !\n");
	else if (err == 2)
		printf("Bad argument value(s) !\n");
	else if (err == 3)
		printf("Malloc error !\n");
	else if (err == 4)
		printf("Bad number arguments !\n");
	else if (err == 5)
		printf("One philosopher always dies (💀)\n");
	else if (err == 6)
		printf("Error creating threads !\n");
	return (err);
}

void	ft_print_bottom_table(int status, int meals)
{
	printf("\u2514---------\u2534--------");
	printf("\u2534-----------------------------\u2534-------\u2518\n");
	if (status)
	{
		printf("     %sALL PHILOSOPHERS HAVE EATEN ", CYAN);
		printf("AT LEAST %s%i%s TIMES%s\n\n", YELLOW, meals, CYAN, NC);
	}
}

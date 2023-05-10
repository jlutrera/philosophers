/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jutrera- <jutrera-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:32:20 by jutrera-          #+#    #+#             */
/*   Updated: 2023/05/02 23:32:20 by jutrera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_inc.h"

int	ft_one_philo(int n)
{
	usleep(n * 1000);
	printf("One philosopher can't eat with one fork, ");
	printf("so it's dead (💀) in ");
	printf("%s%i%s msec.\n", YELLOW, n, NC);
	return (0);
}

void	ft_print_head_table(void)
{
	printf("\n\n     %sPHILOSOPHERS BEGIN TO EAT, ", CYAN);
	printf("SLEEP & THINK !%s      \n", NC);
	printf("\u250c---------\u252c--------\u252c");
	printf("-----------------------------\u2510\n");
	printf("| Lap(ms) | Philo. |            Action           |\n");
	printf("\u251c---------\u253c--------\u253c");
	printf("-----------------------------\u2524\n");
}

int	ft_error_arguments(void)
{
	printf("Bad arguments !. Type:");
	printf("   %s./philo %sarg1 arg2 arg3 arg4 [arg5]%s\n", YELLOW, CYAN, NC);
	printf("    %sarg1:%s number of philosophers.\n", CYAN, NC);
	printf("    %sarg2:%s time to survive without ", CYAN, NC);
	printf("eating (in milisec).\n");
	printf("    %sarg3:%s timme eating (in milisec).\n", CYAN, NC);
	printf("    %sarg4:%s time sleeping (in milisec).\n", CYAN, NC);
	printf("    %sarg5:%s The program will stop if all ", CYAN, NC);
	printf("philosophers eat this number (OPTIONAL).\n");
	return (1);
}

void	ft_print_bottom_table(int status, int meals)
{
	printf("\u2514---------\u2534--------");
	printf("\u2534-----------------------------\u2518\n");
	if (status)
	{
		printf("\n  %sALL PHILOSOPHERS HAVE EATEN ", CYAN);
		printf("AT LEAST %s%i%s TIMES%s\n", YELLOW, meals, CYAN, NC);
	}
}

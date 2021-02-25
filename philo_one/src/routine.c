/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/26 00:25:39 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	life(t_philo *phil)
{
	phil->t[0] = g_ms();	
	while (phil->alive && contr->run)
	{
		phil->t[1] = g_ms();
		if (phil->t[1] - phil->t[0] >= contr->time_to_die)
		{
			print_ts(phil, DIE);
			contr->run = 0;
			break ;
		}
	}
	phil->alive = 0;
}

int		gfork(t_philo *phil, int amt)
{
	if ((amt == 1 && phil->id % 2 == 0) || (amt == 2 && phil->id % 2 != 0))
		return (phil->id);
	else
		return ((phil->id + 1) % contr->nbr_of_philo);
}

int		eat(t_philo *phil)
{

	int id = phil->id;

	int one = (!(id % 2)) ? id + 1 : id;
	int two = (!(id % 2)) ? id : id - 1;

	pthread_mutex_lock(&(contr->forks[one]));
	print_ts(phil, FORK);
 	pthread_mutex_lock(&(contr->forks[two]));
	// pthread_mutex_lock(&(phil->alive_l));
	print_ts(phil, FORK);
	print_ts(phil, EAT);
	phil->t[0] = g_ms();
	zzz(contr->time_to_eat * 1000);
	pthread_mutex_unlock(&(contr->forks[one]));
	pthread_mutex_unlock(&(contr->forks[two]));
	// pthread_mutex_unlock(&(phil->alive_l));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/25 16:45:06 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		isthisreallife(t_philo *phil)
{
	int t;

	sem_wait(phil->alive_l);
	t = phil->alive;
	sem_post(phil->alive_l);
	return (t);
}

void	life(t_philo *phil)
{
	sem_wait(phil->alive_l);
	gettimeofday(&(phil->lmeal), 0);
	sem_post(phil->alive_l);
	// int alive = 1;
	while (1)
	{
		usleep(10);
		if (!check_alive(phil))
		{
			print_ts(phil, DIE);
			return ;
		}
	}
}

// int		gfork(t_philo *phil, int amt)
// {
// 	if ((amt == 1 && phil->id % 2 == 0) || (amt == 2 && phil->id % 2 != 0))
// 		return (phil->id);
// 	else
// 		return ((phil->id + 1) % contr->nbr_of_philo);
// }

int		eat(t_philo *phil)
{
	sem_wait(contr->forks);
	print_ts(phil, FORK);
	sem_wait(contr->forks);
	print_ts(phil, FORK);
	sem_wait((phil->alive_l));
	print_ts(phil, EAT);
	gettimeofday(&(phil->lmeal), 0);
	usleep(contr->time_to_eat * 1000);
	
	sem_post(contr->forks);
	sem_post(contr->forks);
	
	sem_post(phil->alive_l);

	return (0);
}

int		check_alive(t_philo *phil)
{
	struct timeval	time;
	unsigned long	t1;
	unsigned long	t2;

	gettimeofday(&time, 0);
	sem_wait((phil->alive_l));
	t1 = phil->lmeal.tv_sec * 1000000;
	t1 += phil->lmeal.tv_usec + contr->time_to_die * 1000;
	t2 = time.tv_sec * 1000000 + time.tv_usec;
	if (t1 < t2)
	{
		print_ts(phil, DIE);
		phil->alive = 0;
	}
	sem_post(phil->alive_l);
	return (phil->alive);
}

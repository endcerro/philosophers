/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/25 15:41:30 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	life(t_philo *phil)
{
	while (phil->alive)
	{
		// usleep(10);
		if (!check_alive(phil))
			print_ts(phil, DIE);
	}
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
	sem_wait(phil->contr->forks[gfork(phil, 1)]);
	print_ts(phil, FORK);
	sem_wait((phil->contr->forks[gfork(phil, 2)]));
	print_ts(phil, FORK);
	sem_wait((phil->alive_l));
	print_ts(phil, EAT);
	gettimeofday(&(phil->lmeal), 0);
	usleep(phil->contr->time_to_eat * 1000);

	sem_post((phil->contr->forks[gfork(phil, 1)]));
	sem_post((phil->contr->forks[gfork(phil, 2)]));
	sem_post((phil->alive_l));
	
	return (0);
}

int		check_alive(t_philo *phil)
{
	struct timeval	time;
	unsigned long	t1;
	unsigned long	t2;

	gettimeofday(&time, 0);
	sem_wait((phil->alive_l));
	t1 = phil->lmeal.tv_sec * 1000;
	t1 += phil->lmeal.tv_usec / 1000+ phil->contr->time_to_die;
	t2 = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (t1 < t2)
	{
		print_ts(phil, DIE);
		phil->alive = 0;
		phil->contr->end = 1;
	}
	sem_post((phil->alive_l));
	return (phil->alive);
}

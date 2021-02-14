/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/14 17:00:49 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	life(t_philo *phil)
{
	while (phil->alive)
	{
		usleep(10);
		if (!check_alive(phil))
			print_ts(phil, DIE);
	}
}

int		eat(t_philo *phil)
{
	pthread_mutex_lock(&(phil->contr->forks[phil->id]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(phil->contr->forks[(phil->id + 1) %
		phil->contr->nbr_of_philo]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(phil->alive_l));
	print_ts(phil, EAT);
	gettimeofday(&(phil->lmeal), 0);
	usleep(phil->contr->time_to_eat * 1000);
	pthread_mutex_unlock(&(phil->alive_l));
	pthread_mutex_unlock(&(phil->contr->forks[phil->id]));
	pthread_mutex_unlock(&(phil->contr->forks[(phil->id + 1) %
		phil->contr->nbr_of_philo]));
	return (0);
}

int		check_alive(t_philo *phil)
{
	struct timeval	time;
	unsigned long	t1;
	unsigned long	t2;

	gettimeofday(&time, 0);
	pthread_mutex_lock(&(phil->alive_l));
	t1 = phil->lmeal.tv_sec * 1000000;
	t1 += phil->lmeal.tv_usec + phil->contr->time_to_die * 1000;
	t2 = time.tv_sec * 1000000 + time.tv_usec;
	if (t1 < t2)
	{
		print_ts(phil, DIE);
		phil->alive = 0;
		phil->contr->end = 1;
	}
	pthread_mutex_unlock(&(phil->alive_l));
	return (phil->alive);
}

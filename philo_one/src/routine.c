/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/26 00:07:01 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	life(t_philo *phil)
{

	long clock;

	phil->t[0] = g_ms();
	// phil->t[1] = g_ms();
	// while(1)

	
	while (phil->alive && contr->run)
	{
		phil->t[1] = g_ms();
		if (phil->t[1] - phil->t[0] >= contr->time_to_die)
		{
			// pthread_mutex_lock(&contr->)
			// pthread_mutex_lock(&phil->alive_l);
			// printf("DED\n");
			print_ts(phil, DIE);
			contr->run = 0;
			// pthread_mutex_unlock(&phil->alive_l);
			break ;
		}
		
		// printf("ok\n");
	}
	phil->alive = 0;	
	// printf("%li %li\n",phil->t[1], phil->t[0]);
	
	// while (phil->alive)
	// {
	// 	//usleep(10);
	// 	if (!check_alive(phil))
	// 		print_ts(phil, DIE);
	// }
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

	// int nbr = contr->nbr_of_philo;


	// pthread_mutex_lock(&(contr->forks[phil->id]));
	// print_ts(phil, FORK);
	// pthread_mutex_lock(&(contr->forks[(phil->id + 1) %
	// nbr]));
	// print_ts(phil, FORK);





	pthread_mutex_lock(&(contr->forks[gfork(phil, 1)]));
	print_ts(phil, FORK);
 	pthread_mutex_lock(&(contr->forks[gfork(phil, 2)]));
	pthread_mutex_lock(&(phil->alive_l));
	print_ts(phil, FORK);
	print_ts(phil, EAT);
	// usleep(contr->time_to_eat * 500);
	// gettimeofday(&(phil->lmeal), 0);
	phil->t[0] = g_ms();
	zzz(contr->time_to_eat * 1000);
	// pthread_mutex_unlock(&(contr->forks[phil->id]));
	// pthread_mutex_unlock(&(contr->forks[(phil->id + 1) %
	// nbr]));	
	
	pthread_mutex_unlock(&(contr->forks[gfork(phil, 1)]));
	pthread_mutex_unlock(&(contr->forks[gfork(phil, 2)]));
	pthread_mutex_unlock(&(phil->alive_l));
	return (0);
}

// int		check_alive(t_philo *phil)
// {



// 	// struct timeval	time;
// 	unsigned long	t1;
// 	unsigned long	t2;

// 	gettimeofday(&time, 0);
// 	t1 = phil->lmeal.tv_sec * 1000000;
// 	t1 += phil->lmeal.tv_usec + contr->time_to_die * 1000;
// 	t2 = time.tv_sec * 1000000 + time.tv_usec;
// 	pthread_mutex_lock(&(phil->alive_l));
// 	if (t1 < t2)
// 	{
// 		print_ts(phil, DIE);
// 		phil->alive = 0;
// 		contr->end = 1;
// 	}
// 	pthread_mutex_unlock(&(phil->alive_l));
// 	return (phil->alive);
// }

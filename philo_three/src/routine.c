/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/19 15:46:47 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	life(t_philo *phil)
{
	sem_wait(phil->alive_l);
	gettimeofday(&(phil->lmeal), 0);
	sem_post(phil->alive_l);
	while (phil->alive)
	{
		// usleep(10);
		if (!check_alive(phil))
			print_ts(phil, DIE);
	}
}

int 	gfork(t_philo *phil, int amt)
{
	int val;
	if (amt == 1)
	{
		if (phil->id % 2 == 0)
			val = phil->id;
		else
		{
			// printf("nbr = %d \n", contr->nbr_of_philo);
			val = (phil->id + 1) % contr->nbr_of_philo;
			// printf("2 %d getting %d\n", phil->id, val );
			return (val);
		}
	}
	else
	{
		if (phil->id % 2 == 0)
		{
			val = (phil->id + 1) % contr->nbr_of_philo;
			// printf("3 %d getting %d\n",phil->id, val );
			return val;
		}
		else
		{
			val = phil->id;
			// printf("4 %d getting %d\n",phil->id, val );
			return (val);
		}	
	}
	return val;
}

int		eat(t_philo *phil)
{
	// printf("%d w %d\n",phil->id, phil->id );
	sem_wait(contr->forks[gfork(phil, 1)]);
	print_ts(phil, FORK);
	// printf("%d w %d\n", phil->id, gfork(phil, 1) );
	sem_wait((contr->forks[gfork(phil, 2)]));
	print_ts(phil, FORK);
	sem_wait((phil->alive_l));
	print_ts(phil, EAT);
	

	gettimeofday(&(phil->lmeal), 0);
	
	

	usleep(contr->time_to_eat * 1000);

	sem_post((contr->forks[phil->id]));
	sem_post((contr->forks[(phil->id + 1) %
		contr->nbr_of_philo]));
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
	t1 = phil->lmeal.tv_sec * 1000000;
	t1 += phil->lmeal.tv_usec + contr->time_to_die * 1000;
	t2 = time.tv_sec * 1000000 + time.tv_usec;
	// printf("%lu, %lu\n", t1, t2);
	if (t1 < t2)
	{
		// printf("DEATH TIME\n");
		print_ts(phil, DIE);
		// sem_wait(contr->done);
		
		// contr->end = 1;
		// sem_post(contr->done);
		sem_wait(phil->alive_l);
		phil->alive = 0;
		sem_post(phil->alive_l);
		
		
		// printf("OK WE DID DIE\n");

		sem_post((phil->alive_l));
		// printf("RETURN TIME\n");
		return (0);
	}
	else
		// printf("why tho\n");
	sem_post((phil->alive_l));
	// printf("IS DONE %d\n",phil->id );
	return (phil->alive);
}

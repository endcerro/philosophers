/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2020/12/07 22:34:17 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void init_contr(t_contr *contr)
{
	int i = 0;


	contr->nbr_of_philo = 2;
	contr->time_to_die = 4000; //5 Sec before dying
	contr->time_to_eat = 3000; //2 Sec to eat
	contr->time_to_sleep = 1000; //1 Sec to sleep

	
	contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo);
	while(i < contr->nbr_of_philo)
	{
		pthread_mutex_init(&(contr->forks[i++]), 0);
	}
	pthread_mutex_init(&(contr->stdout), 0);
}

int check_alive(t_philo *phil)
{
	struct timeval time;
	struct timeval lifespan;

	gettimeofday(&time, 0);

/*	unsigned long life = 0;
	unsigned long untill = 0;
	life += phil->lmeal.tv_sec * 1000; 	//sec to ms
	life += phil->lmeal.tv_usec / 1000;	//usec to ms
	life += phil->contr->time_to_eat;	//ms to ms
	untill += time.tv_sec * 1000;		//sec to ms
	untill += time.tv_usec / 1000;		//usec to ms
	if (life > untill)
		return 1;
	return (0);
*/

	lifespan = phil->lmeal;

	lifespan.tv_usec += phil->contr->time_to_die * 1000;
	while (lifespan.tv_usec >= 1000000)
	{
		lifespan.tv_usec -= 1000000;
		lifespan.tv_sec += 1;
	}
	if (time.tv_sec > lifespan.tv_sec)
		return (0);
	else if (time.tv_sec == lifespan.tv_sec && time.tv_sec >= lifespan.tv_usec)
		return (0);
	
	return (1);
}

// pthread_mutex_t *getforks(t_philo *phil)
// {
// 	pthread_mutex_t mtx[2];

// 	mtx[0] = phil->contr->forks[phil->id];
// 	mtx[1] = phil->contr->forks[phil->id + 1 % phil->contr->nbr_of_philo];

// 	return (mtx);
// }

int sleepcheck(unsigned int zzz, t_philo *phil)
{
	unsigned int t;
	int quot;

	quot = 10;

	t = zzz / quot;
	int i = 0;
	while(i < quot)
	{
		usleep(t);
		// t += zzz / 10;
		if (!check_alive(phil))
			return (1);
	}
	return (0);
}


int eat(t_philo *phil)
{
	// pthread_mutex_t forks[2];
	int ret;

	ret = 1;
	// forks[0] = phil->contr->forks[phil->id];
	// forks[1] = phil->contr->forks[(phil->id + 1) % phil->contr->nbr_of_philo];

	pthread_mutex_lock(&(phil->contr->forks[phil->id]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(phil->contr->forks[(phil->id + 1) % phil->contr->nbr_of_philo]));
	print_ts(phil, FORK);
	if (check_alive(phil))
	{
		print_ts(phil, EAT);
		usleep(phil->contr->time_to_eat * 1000);
		gettimeofday(&(phil->lmeal), 0);
		// usleep(phil->contr->time_to_eat * 1000);
		ret--;
	}
	else
		print_ts(phil, DIE);
	// else
	// {
	// 	printf("Oh no %d should die \n", phil->id);	
	// }

	pthread_mutex_unlock(&(phil->contr->forks[phil->id]));
	pthread_mutex_unlock(&(phil->contr->forks[(phil->id + 1) % phil->contr->nbr_of_philo]));

	// pthread_mutex_unlock(&(forks[0]));
	// pthread_mutex_unlock(&(forks[1]));

	return (ret);
}


void loop(t_philo *phil)
{
	phil->alive = 1;

	gettimeofday(&(phil->lmeal), 0);
	while(phil->alive)
	{
		if (!check_alive(phil))
		{
			return print_ts(phil, DIE);
		}
		// eat(phil);
		if (eat(phil) == 1)
			return ;//rint_ts(phil, DIE);
		// print_ts(phil, EAT);
		// if (sleepcheck(phil->contr->time_to_sleep * 1000, phil))
		// {
		// 	printf("%d died in his sleep", phil->id);
		// 	return;
		// }
		print_ts(phil, SLEEP);
		usleep(phil->contr->time_to_sleep * 1000); //Usleeep uses microseconds
	}

	return;
}

void spawn_philos(t_contr *contr)
{
	int i;

	pthread_t pid[contr->nbr_of_philo];
	t_philo philos[contr->nbr_of_philo];

	gettimeofday(&(contr->start), 0);
	i = -1;
	while(++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		pthread_create(&(pid[i]), 0, (void*)loop, (void*)&(philos[i]));
	}
	i = -1;
	while(++i < contr->nbr_of_philo)
	{
		pthread_join(pid[i], 0);
	}
}


void cleanup(t_contr *contr)
{
	int i = 0;
	while(i < contr->nbr_of_philo)
	{
		pthread_mutex_destroy(&(contr->forks[i++]));
	}
	free(contr->forks);
	pthread_mutex_destroy(&(contr->stdout));
}

int main()
{
	t_contr contrn;

	contr = &contrn;
	init_contr(&contrn);
	spawn_philos(&contrn);
	cleanup(&contrn);
	
	return 0;
}
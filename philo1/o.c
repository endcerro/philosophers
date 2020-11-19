/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2020/11/01 18:55:44 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"


int init(int argc, char **argv, t_contr *contr)
{
	// if (argc < 5 || argc > 6)
	// {
	// 	printf("ERROR ARG COUNT\n");
	// 	return (1);
	// }
	// contr->nbr_of_philo = (unsigned int)ft_atoi(argv[1]);
	// contr->time_to_die = (unsigned int)ft_atoi(argv[2]);
	// contr->time_to_eat = (unsigned int)ft_atoi(argv[3]);
	// contr->time_to_sleep = (unsigned int)ft_atoi(argv[4]);
	contr->nbr_of_philo = 2;
	contr->time_to_die = 10000;
	contr->time_to_eat = 1000;
	contr->time_to_sleep = 5000;
	contr->must_eat = -1;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->print_lock = 0;

	// contr->forks = malloc(sizeof(int) * contr->nbr_of_philo);

	int i = -1;
	// while (++i < contr->nbr_of_philo)
	// 	contr->forks[i] = 1;

	// pthread_mutex_init(&(contr->mutex), 0);


	return (0);
}






void life_loop(void *arg)
{
	t_philo *phil = (t_philo*)arg;
	int run = 1;

	struct timeval t;
	unsigned long diff;
	
	
	while (run)
	{
		gettimeofday(&t, 0);

		pthread_mutex_lock(&(phil->food_mtx));
		
		if (t.tv_usec - phil->ate->tv_usec > phil->ttdie)
		{
			pthread_mutex_unlock(&(phil->food_mtx));
			printf("IT SHOULD DIE\n");
			pthread_mutex_lock(&(phil->alive_mtx));
			(phil->alive) = 0;
			run = 0;
			pthread_mutex_unlock(&(phil->alive_mtx));
			
		}
		else
		{
			printf("NOT DEAD YET\n");
		}
		// phil->ttdie -= 100;
	}

	printf("DONE CHECKING IF ALIVE\n");
	
	// usleep(500000);
	// pthread_mutex_lock(&(phil->alive_mtx));
	// (phil->alive) = 0;
	// pthread_mutex_unlock(&(phil->alive_mtx));

}


void loop(void *arg)
{

	t_contr *contr = arg;
	t_philo phil;
	phil.id = 1;

	phil.alive = 1;

	pthread_mutex_init(&(phil.alive_mtx), 0);
	pthread_mutex_init(&(phil.food_mtx), 0);

	pthread_t pid;

	pthread_create(&pid, 0, (void *)life_loop, (void *)&phil);


	gettimeofday(phil.ate, 0);


	while (!pthread_mutex_lock(&(phil.alive_mtx)) && phil.alive)
	{
		pthread_mutex_unlock(&(phil.alive_mtx));
		usleep(5000);
		pthread_mutex_lock(&(phil.food_mtx));

		gettimeofday(phil.ate, 0);

		pthread_mutex_unlock(&(phil.food_mtx));


	}
	printf("Philo %d is ded\n",phil.id);
	pthread_join(pid, 0);

}


void run(void *arg)
{
	t_philo *phil = arg;

	pthread_t pid;
	

	struct timeval eat;
	

	phil->ate = &eat;

	unsigned int ttwait = 10;

	pthread_create(&pid, 0, (void *)life_loop, phil);



	printf("Philo nb %d spawned\n",phil->id);

	while (pthread_mutex_lock(&(phil->alive_mtx)) && phil->alive)
	{
		pthread_mutex_unlock(&(phil->alive_mtx));

		// printf("Philo nb %d alive\n",phil->id);
		// usleep(ttwait);l

		gettimeofday(&eat, 0);

		// printf("Philo nb %d ate\n",phil->id);
		// ttwait += 100;
		//eat

		//think
		//sleep


	}

}

void start(t_contr *contr)
{
	int i = 0;

	pthread_t pid;

	pthread_create(&pid, 0, (void *)loop, 0);
	pthread_join(pid, 0);
}





void spawn_philos(t_contr *contr)
{
	int i = 0;


	pthread_t pid[contr->nbr_of_philo];


	t_philo phil[contr->nbr_of_philo];

	for(int j = 0; j < contr->nbr_of_philo; j++)
	{
		phil[i].id = j;
		phil[i].contr = contr;
	}




	while(i < contr->nbr_of_philo)
	{
		if (pthread_create(&(pid[i]), 0, (void *)run, (void *)&(phil[i])))
			printf("GOT AN ISSUE\n");
		else
			ft_putstr("spawn ok\n" );
		i++;
	}
	
	i = 0;
	while(i < contr->nbr_of_philo)
	{
		pthread_join(pid[i], 0);
		i++;
	}

}


int main(int argc, char **argv)
{
	t_contr contr;
	t_test test;


	test.id = 0;
	
	if (init(argc, argv, &contr))
		return (1);
	
	spawn_philos(&contr);
	

	return (0);
}
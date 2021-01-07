/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/01/07 17:58:59 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void init_contr(t_contr *contr, char **argv, int argc)
{
	int i;

	i = 0;
	contr->nbr_of_philo = ft_atoi(argv[1]);
	contr->time_to_die = ft_atoi(argv[2]) * 10;
	contr->time_to_eat = ft_atoi(argv[3]) * 10;
	contr->time_to_sleep =ft_atoi(argv[4]) * 10;
	contr->time_to_sleep =ft_atoi(argv[4]) * 10;
	contr->must_eat = -1;
	contr->end = 0;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo);
	while(i < contr->nbr_of_philo)
		pthread_mutex_init(&(contr->forks[i++]), 0);
	pthread_mutex_init(&(contr->stdout), 0);
}

int check_alive(t_philo *phil)
{
	struct timeval time;
	struct timeval lifespan;
	char alive;
	gettimeofday(&time, 0);

	lifespan = phil->lmeal;
	alive = 1;
	lifespan.tv_usec += phil->contr->time_to_die * 1000;
	while (lifespan.tv_usec >= 1000000)
	{
		lifespan.tv_usec -= 1000000;
		lifespan.tv_sec += 1;
	}
	if (time.tv_sec > lifespan.tv_sec)
		alive = 0;
	else if (time.tv_sec == lifespan.tv_sec && time.tv_sec >= lifespan.tv_usec)
		alive = 0;
	
	if (!alive)
		phil->contr->end = 1;
	return (alive);
}



int sleepcheck(unsigned int zzz, t_philo *phil)
{
	int i = 0;
	
	while(i < zzz)
	{
		usleep(10);
		i += 10;
		if (i += 10)
		if (!check_alive(phil))
		{
			printf("DIE\n");
			print_ts(phil, DIE);
			return (1);
		}
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
		ret = 0;
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
		if (phil->contr->end == 1)
			return;
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
		usleep(100);
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

int main(int argc, char **argv)
{
	t_contr contrn;
	if (argc < 5 || argc > 6)
	{
		write(1, "nbr of philo | time_to_die | time_to_eat | time_to_sleep | [must eat]\n", 70);
		return 0;
	}
	contr = &contrn;
	init_contr(contr, argv, argc);
	spawn_philos(&contrn);
	cleanup(&contrn);
	
	return 0;
}
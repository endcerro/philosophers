/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/01/10 16:37:48 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void init_contr(t_contr *contr, char **argv, int argc)
{
	int i;

	i = 0;
	contr->nbr_of_philo = ft_atoi(argv[1]);
	contr->time_to_die = ft_atoi(argv[2]);
	contr->time_to_eat = ft_atoi(argv[3]);
	contr->time_to_sleep =ft_atoi(argv[4]);
	contr->time_to_sleep =ft_atoi(argv[4]);
	contr->must_eat = -1;
	contr->end = 0;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo);
	while(i < contr->nbr_of_philo)
		pthread_mutex_init(&(contr->forks[i++]), 0);
}

int check_alive(t_philo *phil)
{
	struct timeval time;
	unsigned long t1;
	unsigned long t2;

	gettimeofday(&time, 0);
	t1 = phil->lmeal.tv_sec * 1000000;
	t1 += phil->lmeal.tv_usec + phil->contr->time_to_die * 1000;
	t2 = time.tv_sec * 1000000 + time.tv_usec;
	if (t1 < t2)
	{
		print_ts(phil, DIE);
		phil->alive = 0;
		phil->contr->end = 1;
	}
	return (phil->alive);
}



int sleepcheck(unsigned int zzz, t_philo *phil)
{
	// unsigned int i = 0;
	// while(i < zzz && phil->alive && !phil->contr->end)
	// {
	// 	usleep(10);
	// 	i += 10;
	// }
	usleep(zzz);
	return (0);
}


int eat(t_philo *phil)
{
	pthread_mutex_lock(&(phil->contr->forks[phil->id]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(phil->contr->forks[(phil->id + 1) % phil->contr->nbr_of_philo]));
	print_ts(phil, FORK);
	
	pthread_mutex_lock(&(phil->alive_l));
	print_ts(phil, EAT);
	sleepcheck(phil->contr->time_to_eat * 1000, phil);
	gettimeofday(&(phil->lmeal), 0);
	pthread_mutex_unlock(&(phil->alive_l));

	pthread_mutex_unlock(&(phil->contr->forks[phil->id]));
	pthread_mutex_unlock(&(phil->contr->forks[(phil->id + 1) % phil->contr->nbr_of_philo]));

	return (0);
}


void loop(t_philo *phil)
{
	phil->alive = 1;
	gettimeofday(&(phil->lmeal), 0);
	int cpt;

	cpt = 0;	
	while(phil->alive && !phil->contr->end)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == phil->contr->must_eat)
		{
			phil->contr->did_eat++;
			phil->alive = 0;
			break;
		}
		print_ts(phil, SLEEP);
		sleepcheck(phil->contr->time_to_sleep * 1000, phil);
	}
	return;
}

void life(t_philo *phil)
{
	while (phil->alive)
	{
		usleep(10);
		pthread_mutex_lock(&(phil->alive_l));
		if (!check_alive(phil))
			print_ts(phil, DIE);
		pthread_mutex_unlock(&(phil->alive_l));
	}
}

void spawn_philos(t_contr *contr)
{
	int i;

	pthread_t pid[contr->nbr_of_philo];
	pthread_t pid_l[contr->nbr_of_philo];
	t_philo philos[contr->nbr_of_philo];

	contr->did_eat = 0;
	gettimeofday(&(contr->start), 0);
	i = -1;
	while(++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		pthread_mutex_init(&(philos[i].alive_l), 0);
		pthread_create(&(pid[i]), 0, (void*)loop, (void*)&(philos[i]));
		pthread_create(&(pid_l[i]), 0, (void*)life, (void*)&(philos[i]));
		usleep(50);
	}
	i = -1;

	while(++i < contr->nbr_of_philo)
	{
		pthread_mutex_destroy(&(philos[i].alive_l));
		pthread_join(pid_l[i], 0);
	}
	if (contr->did_eat == contr->nbr_of_philo)
		write(1, "All philos ate as supposed\n", 27);
}


void cleanup(t_contr *contr)
{
	int i = 0;
	while(i < contr->nbr_of_philo)
	{
		pthread_mutex_destroy(&(contr->forks[i++]));
	}
	free(contr->forks);
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
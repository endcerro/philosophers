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

void init_contr(t_contr *contr)
{
	int i = 0;


	contr->nbr_of_philo = 3;
	contr->time_to_die = 5000; //5 Sec before dying
	contr->time_to_eat = 2000; //2 Sec to eat
	contr->time_to_sleep = 1000; //1 Sec to sleep

	
	contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo);
	while(i < contr->nbr_of_philo)
	{
		pthread_mutex_init(&(contr->forks[i++]), 0);
	}
	pthread_mutex_init(&(contr->stdout), 0);
}


void print_ts(t_philo *phil, int action)
{
	struct timeval delta;
	long int s;
	unsigned int ms;


	gettimeofday(&delta, 0);
	s = delta.tv_sec - phil->contr->start.tv_sec;
	ms = (delta.tv_usec - phil->contr->start.tv_usec) / 1000;


	pthread_mutex_lock(&(phil->contr->stdout));

	//TO CHANGE
	// ft_putnbr_l(s);
	// write(1," ", 1);
	// ft_putunbr(ms);
	// write(1," ", 1);
	// ft_putnbr(phil->id);

	if (action == FORK)
		ft_putstr(" has taken a fork\n");
	else if (action == EAT)	
		ft_putstr(" is eating\n");
	else if (action == SLEEP)
		ft_putstr(" is sleeping\n");
	else if (action == THINK)
		ft_putstr(" is thinking\n");
	else if (action == DIE)
		ft_putstr(" died\n");

	pthread_mutex_unlock(&(phil->contr->stdout));

}


void print(char *str, t_contr *contr)
{
	pthread_mutex_lock(&(contr->stdout));
	ft_putstr(str);
	pthread_mutex_unlock(&(contr->stdout));
}

void print_nb(char *str, int i, t_contr *contr)
{
	pthread_mutex_lock(&(contr->stdout));
	ft_putstr(str);
	ft_putnbr(i);
	write(1,"\n",1);
	pthread_mutex_unlock(&(contr->stdout));
}

int check_alive(t_philo *phil)
{
	struct timeval time;
	struct timeval lifespan;

	gettimeofday(&time, 0);
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


void loop(t_philo *phil)
{
	phil->alive = 1;

	gettimeofday(&(phil->lmeal), 0);
	while(phil->alive)
	{
		if (!check_alive(phil))
		{
			print_nb("It died", phil->id, phil->contr);
			return ;
		}
		print_ts(phil, EAT);
		usleep(phil->contr->time_to_sleep * 1000); //Usleeep uses microseconds
	}

	return;
}

void spawn_philos(t_contr *contr)
{
	int i;

	pthread_t pid[contr->nbr_of_philo];
	t_philo philos[contr->nbr_of_philo];

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
	t_contr contr;

	init_contr(&contr);
	spawn_philos(&contr);
	cleanup(&contr);
	
	return 0;
}
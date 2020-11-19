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
	contr->time_to_die = 500000; //5 sec
	contr->time_to_eat = 1000000; //1 sec
	contr->time_to_sleep = 3000000; //3sec
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

void printline(char *str, int val)
{
	ft_putstr(str);
	ft_putnbr(val);
	write(1, "\n", 1);
}

void death_loop(t_philo *philo)
{

	int alive;

	
	alive = 1;
	struct timeval time;
	//; //Get time of its start
	// printline("Death spawn", philo->id);


	unsigned long ttdie = 10;


	while (alive)
	{
		gettimeofday(&time, 0);
		// printf("delta is %ld\n",time.tv_sec - philo->ate.tv_sec );
		if (time.tv_usec - philo->ate.tv_usec >= philo->contr->time_to_die)
		{
			// if(philo->id == 0)
			printline("it should die", philo->id);
			philo->alive = 0;
			return;
		}
		else
		{
			// if(philo->id == 0)
				// printf("we fine\n");
		}
	}
}

void life_loop(t_philo *philo)
{
	printline("Philo spawn", philo->id);

	int run = 1;

	pthread_t pid;
	philo->alive = 1;

	gettimeofday(&(philo->ate), 0);
	pthread_create(&pid, 0, (void *)death_loop, (void *)philo); //Create death checker
	


	unsigned long ttsleep = 50;


	while(philo->alive)
	{

		
		pthread_mutex_lock(&(philo->contr->mutex[0]));
		printline("has taken 1 fork", philo->id);
		

		pthread_mutex_lock(&(philo->contr->mutex[1]));
		printline("has taken 2 fork", philo->id);


		printline("is eating", philo->id);
		usleep(philo->contr->time_to_eat);

		gettimeofday(&(philo->ate), 0);

		pthread_mutex_unlock(&(philo->contr->mutex[0]));
		pthread_mutex_unlock(&(philo->contr->mutex[1]));
			
		printline("drop 2 fork", philo->id);

		
		printline("philo gonna sleep", philo->id);
		usleep(philo->contr->time_to_sleep);

		
		
		// ttsleep *=2;
	}
	printline("Philo rm", philo->id);
}

void spawn(t_contr *contr)
{
	int i;
	pthread_t pid[contr->nbr_of_philo];
	t_philo philo[contr->nbr_of_philo];




	i = 0;

	while( i < contr->nbr_of_philo)
	{
		pthread_mutex_init(&(contr->mutex[i]), 0);
		philo[i].contr = contr;
		philo[i].id = i;
		pthread_create(&(pid[i]), 0, (void *)life_loop, (void *)&(philo[i]));
		i++;
	}
	i = 0;
	while( i < contr->nbr_of_philo)
	{
		pthread_join(pid[i], 0);
		i++;
	}
	for(int j = 0; j < contr->nbr_of_philo; j++)
		pthread_mutex_destroy(&(contr->mutex[j]));
}


int main(int argc, char **argv)
{
	t_contr contr;
	init(argc, argv, &contr);
	/* code */
	spawn(&contr);
	return 0;
}
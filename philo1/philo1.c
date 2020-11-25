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
	contr->nbr_of_philo = 	2;
	contr->time_to_die = 	5000; //5 sec
	contr->time_to_eat = 	2000000; //1 sec
	contr->time_to_sleep = 	1000000; //3sec
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
	struct timeval t;

	gettimeofday(&t, 0),

	alive = 1;
	while (alive)
	{
		if (pthread_mutex_lock(&(philo->food_mtx)) == 0 && t.tv_usec >= philo->alive_untill.tv_usec)
		{
			printline("it should die", philo->id);
			philo->alive = 0;
		}
		pthread_mutex_unlock(&(philo->food_mtx));
	}
}

void p_ts(t_contr *contr)
{
	struct timeval t;

	gettimeofday(&t, 0);
	ft_putnbr_l((t.tv_usec - contr->start.tv_usec) / 1000);
}

void p_action(t_philo *p, int action)
{
	pthread_mutex_lock(&(p->contr->stdout));
	p_ts(p->contr);
	write(1," ",1);
	ft_putnbr(p->id);
	if (action == 0)
		ft_putstr(" has taken a fork\n");
	else if(action == 1)
		ft_putstr(" is eating\n");
	else if(action == 2)
		ft_putstr(" is sleeping\n");
	else if(action == 3)
		ft_putstr(" is thinking\n");
	else if(action == 4)
		ft_putstr(" died\n");

	pthread_mutex_unlock(&(p->contr->stdout));
}


void getforks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->contr->mutex[0])); 						//Lock first fork
	p_action(philo, 0);													//Announce it
		

	pthread_mutex_lock(&(philo->contr->mutex[1]));						//Lock second fork
	p_action(philo, 0);													//Announce it

}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->food_mtx));								//Locking food
	p_action(philo, 1);													//Announce it
	usleep(philo->contr->time_to_eat);									//Eating time

	gettimeofday(&(philo->alive_untill), 0);							//Reset time
	philo->alive_untill.tv_usec += 1000 * philo->contr->time_to_die;	//Add lifespan
	if(philo->alive_untill.tv_usec >= 1000000)
	{
		philo->alive_untill.tv_usec -= 1000000;
		philo->alive_untill.tv_sec += 1;
	}

	pthread_mutex_unlock(&(philo->food_mtx));							//Release food
}

void dropforks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->contr->mutex[0]));					//Release fork
	pthread_mutex_unlock(&(philo->contr->mutex[1]));					//Release fork
}


// void life_loop(t_philo *philo)
// {
// 	int run = 1;
// 	pthread_t pid;
	
// 	philo->alive = 1;

// 	gettimeofday(&(philo->alive_untill), 0); 								//Getting spawn time
// 	philo->alive_untill.tv_usec += 1000 * philo->contr->time_to_die; 		//Adding lifespan in ms
	

// 	pthread_mutex_init(&(philo->food_mtx), 0);




// 	pthread_create(&pid, 0, (void *)death_loop, (void *)philo); 			//Create death checker
	

// 	while(philo->alive)
// 	{

// 		getforks(philo);

// 		eat(philo);

// 		dropforks(philo);

// 		p_action(philo, 2);													//Announce sleep
// 		usleep(philo->contr->time_to_sleep);								//Sleep
// 	}
// 	p_action(philo, 4);														//Announce death
// }

void spawn(t_contr *contr)
{
	int i;
	pthread_t pid[contr->nbr_of_philo];
	t_philo philo[contr->nbr_of_philo];




	i = 0;

	gettimeofday(&(contr->start), 0);

	pthread_mutex_init(&(contr->stdout), 0);

	while( i < contr->nbr_of_philo)
	{
		pthread_mutex_init(&(contr->mutex[i]), 0);
		philo[i].contr = contr;
		philo[i].id = i;
		pthread_mutex_init(&((philo[i]).philo_mtx), 0);
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
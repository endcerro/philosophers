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
	contr->time_to_die = 	100000;		// 	10 Secs before dying
	contr->time_to_eat = 	2000; 		//	2 Secs to eat
	contr->time_to_sleep = 	3000; 		//	3 Secs to sleep
	contr->must_eat = -1;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->print_lock = 0;

	return (0);
}

void printline(char *str, int val)
{
	ft_putstr(str);
	ft_putnbr(val);
	write(1, "\n", 1);
}

void p_ts(t_contr *contr)
{
	struct timeval t;

	gettimeofday(&t, 0);
	
	int sec = t.tv_sec - contr->start.tv_sec;
	int usec = t.tv_usec - contr->start.tv_usec;


	if (usec < 0)
	{
		sec--;
		usec += 1000000;
	}
	
	ft_putnbr(sec);
	write(1," ", 1);
	
	ft_putnbr(usec);


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
	// p_action(philo, 0);													//Announce it
		

	pthread_mutex_lock(&(philo->contr->mutex[1]));						//Lock second fork
	p_action(philo, 0);													//Announce it

}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->philo_mtx));								//Locking food
	p_action(philo, 1);													//Announce it
	usleep(philo->contr->time_to_eat);									//Eating time

	add_lifespan(philo);
	// gettimeofday(&(philo->alive_untill), 0);							//Reset time
	// philo->alive_untill.tv_usec += (1000 * philo->contr->time_to_die);	//Add lifespan
	// if(philo->alive_untill.tv_usec >= 1000000)
	// {
	// 	philo->alive_untill.tv_usec -= 1000000;
	// 	philo->alive_untill.tv_sec += 1;
	// }

	pthread_mutex_unlock(&(philo->philo_mtx));							//Release food
}

void dropforks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->contr->mutex[0]));					//Release fork
	pthread_mutex_unlock(&(philo->contr->mutex[1]));					//Release fork
}


void spawn(t_contr *contr)
{
	int i;
	pthread_t 	pid[contr->nbr_of_philo];		//PID ARRAY
	t_philo 	philo[contr->nbr_of_philo];		//Struct array




	i = 0;

	gettimeofday(&(contr->start), 0);			//Timer since the start of program

	pthread_mutex_init(&(contr->stdout), 0);	//stdout mutex for collisions


	while( i < contr->nbr_of_philo) 			//Setup philos
	{
		pthread_mutex_init(&(contr->mutex[i]), 0);			//TO CHANGE
		philo[i].contr = contr;								//Contr link
		philo[i].id = i;									//Id set
		pthread_mutex_init(&((philo[i]).philo_mtx), 0);		//Init philo mtx
		pthread_create(&(pid[i]), 0, (void *)life_loop, (void *)&(philo[i])); //Start
		i++;
	}



	i = 0;
	while( i < contr->nbr_of_philo)
	{
		pthread_join(pid[i], 0);
		i++;
	}
	for(int j = 0; j < contr->nbr_of_philo; j++)
	{
		pthread_mutex_destroy(&(philo[j].philo_mtx));
		pthread_mutex_destroy(&(contr->mutex[j]));
	}
}


int main(int argc, char **argv)
{
	t_contr contr;
	init(argc, argv, &contr);
	/* code */
	spawn(&contr);
	return 0;
}
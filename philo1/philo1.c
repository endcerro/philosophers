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

typedef struct m_philo
{
	int last_meal;
}	t_philo;


int init(int argc, char **argv, t_contr *contr)
{
	if (argc < 5 || argc > 6)
	{
		printf("ERROR ARG COUNT\n");
		return (1);
	}
	contr->nbr_of_philo = (unsigned int)ft_atoi(argv[1]);
	contr->time_to_die = (unsigned int)ft_atoi(argv[2]);
	contr->time_to_eat = (unsigned int)ft_atoi(argv[3]);
	contr->time_to_sleep = (unsigned int)ft_atoi(argv[4]);
	contr->must_eat = -1;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->print_lock = 0;

	contr->forks = malloc(sizeof(int) * contr->nbr_of_philo);

	int i = -1;
	while (++i < contr->nbr_of_philo)
		contr->forks[i] = 1;

	return (0);
}

void loop()
{
	int alive = 1;

	//eat
	//sleep
	//think
}


void spawn_philo(t_contr *contr)
{
	// pthread_t pid;
	// pthread_create(&pid, 0, &memes, (void *)contr);
	// pthread_join(pid, NULL);
}



int main(int argc, char **argv)
{
	t_contr contr;

	if (init(argc, argv, &contr))
		return (1);
	//spawn_philo(&contr);
	return (0);
}
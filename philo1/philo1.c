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
	// if (argc < 5 || argc > 6)
	// {
	// 	printf("ERROR ARG COUNT\n");
	// 	return (1);
	// }
	// contr->nbr_of_philo = (unsigned int)ft_atoi(argv[1]);
	// contr->time_to_die = (unsigned int)ft_atoi(argv[2]);
	// contr->time_to_eat = (unsigned int)ft_atoi(argv[3]);
	// contr->time_to_sleep = (unsigned int)ft_atoi(argv[4]);
	contr->nbr_of_philo = 1;
	contr->time_to_die = 10000;
	contr->time_to_eat = 1000;
	contr->time_to_sleep = 5000;
	contr->must_eat = -1;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	contr->print_lock = 0;

	contr->forks = malloc(sizeof(int) * contr->nbr_of_philo);

	int i = -1;
	while (++i < contr->nbr_of_philo)
		contr->forks[i] = 1;

	pthread_mutex_init(&(contr->mutex), 0);


	return (0);
}

int comp_tz(struct timeval one, struct timeval two)
{
	// return (one->)
	return 1;
}

void loop(void *arg)
{
	t_contr *contr = (t_contr *)arg;
	struct timeval sp;
	struct timeval new;
	int alive = 1;
	int spawn = gettimeofday(&sp, NULL);
	
	while(alive)
	{
		spawn = gettimeofday(&new, NULL);
		printf("SLEEPING \n");
		usleep(contr->time_to_sleep);
		usleep(contr->time_to_sleep);

		if (new.tv_usec > sp.tv_usec + contr->time_to_die)
		{
			printf("philo died\n");
			alive = 0;
		}
		else
		{
			pthread_mutex_lock(&(contr->mutex));

			printf("FOOD TIME\n");
			usleep(contr->time_to_eat);
			pthread_mutex_unlock(&(contr->mutex));
			spawn = gettimeofday(&sp, NULL);
		}
		
	}
	//eat
	//sleep
	//think
	printf("philo died\n");
}
void testloop(void *arg)
{
	t_test *test = (t_test *) arg;

	
	int alive = 1;
	printf("test->id = %d\n",test->id );

	int mtxrights = 0;
	while (alive < 1000)
	{
		

		// pthread_mutex_lock(test->check);



		// if (*(test->lock) == 1)
		// {
		// 	// printf("Fork n%d has to wait\n",test->id);
		// 	int mtxrights = 1;
		// 	pthread_mutex_unlock(test->check);
		// }
		// else
		// {
			// *(test->lock) = 1;
			pthread_mutex_lock((test->mutex));
			pthread_mutex_lock((test->check));
			// pthread_mutex_unlock(test->check);


			printf("Fork n%d got the mutex at time\n",test->id);
			pthread_mutex_unlock((test->mutex));
			usleep(10);
			
			pthread_mutex_unlock((test->check));
			// usleep(10);

			// printf("Fork n%d left the mutex\n",test->id);

			// pthread_mutex_lock(test->check);
			// *(test->lock) = 0;
			// pthread_mutex_unlock((test->check));
		//}

		
	}

	// struct timeval spawn;
	// struct timeval current;
	
	// int alive = 1;
	
	// gettimeofday(&spawn, NULL);
	
	// pthread_mutex_lock((test->mutex));
	// printf("Fork n%d got the mutex at time\n",test->id);
	// usleep(5000000);
	// pthread_mutex_unlock((test->mutex));
	// printf("Fork n%d left the mutex\n",test->id);
}


void spawn_philo(t_contr *contr, t_test *test)
{
	

	pthread_t pid[2];

	int i = 0;
	// while(i < contr->nbr_of_philo)

	// {
		
		t_test t1;
		t_test t2;

		int lock;

		lock = 0;

		t1.id = 0;
		t2.id = 1;

		pthread_mutex_t mute;
		pthread_mutex_init(&(mute), 0);

		pthread_mutex_t check;
		pthread_mutex_init(&(check), 0);


		t1.mutex = &mute;
		t2.mutex = &mute;

		t1.check = &check;
		t2.check = &check;

		t1.lock = &lock;
		t2.lock = &lock;

		pthread_create(&(pid[0]), 0, (void *)&testloop, (void *)&t1);
		pthread_create(&(pid[1]), 0, (void *)&testloop, (void *)&t2);	
	// 	// i++;
	// // }
	
	// // i = 0;
	// // while(i < contr->nbr_of_philo)
	// // {
		pthread_join(pid[0], NULL);
		
		pthread_join(pid[1], NULL);
		// i++;
		pthread_mutex_destroy(&mute);
		pthread_mutex_destroy(&check);
	// }
}



int main(int argc, char **argv)
{
	t_contr contr;
	t_test test;

	test.id = 0;
	// pthread_mutex_init(&(test.mutex), 0);

	// if (init(argc, argv, &contr))
	// 	return (1);
	spawn_philo(&contr, &test);
	// pthread_mutex_destroy((test.mutex));
	return (0);
}
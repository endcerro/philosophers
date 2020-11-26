#include "philo1.h"


void add_lifespan(t_philo *philo)
{
	gettimeofday(&(philo->alive_untill), 0); //Get curr time							

	
	philo->alive_untill.tv_usec += (1000 * philo->contr->time_to_die);	//Add lifespan
	if(philo->alive_untill.tv_usec >= 1000000)
	{
		printf("S VAL = %ld\n",philo->alive_untill.tv_sec);
		printf("US VAL = %ld\n",philo->alive_untill.tv_usec);
		philo->alive_untill.tv_usec -= 1000000;
		philo->alive_untill.tv_sec += 1;
	}
}


void prep_philo(t_philo *philo)
{
	philo->alive = 1;
	pthread_mutex_init(&(philo->philo_mtx), 0);


	add_lifespan(philo);
	// gettimeofday(&(philo->alive_untill), 0); 								//Getting spawn time
	// philo->alive_untill.tv_usec += (1000 * philo->contr->time_to_die);		//Adding lifespan in ms
	
	// if(philo->alive_untill.tv_usec >= 1000000)
	// {
	// 	philo->alive_untill.tv_usec -= 1000000;
	// 	philo->alive_untill.tv_sec += 1;
	// }

}

void routine_loop(t_philo *philo)
{
	while(philo->alive)
	{

		getforks(philo);

		eat(philo);

		dropforks(philo);

		p_action(philo, 2);													//Announce sleep
		usleep(philo->contr->time_to_sleep);								//Sleep
	}
}


int dies(t_philo *philo, struct timeval time)
{
	pthread_mutex_lock(&(philo->philo_mtx));

	if (time.tv_sec > philo->alive_untill.tv_sec)
	{
		printf("D1\n");
		return 1;
	}
	else if (time.tv_sec == philo->alive_untill.tv_sec)
	{
		if (time.tv_usec > philo->alive_untill.tv_usec)
		{
			printf("D2\n");
			return 1;
		}
	}

	philo->alive = 0;
	pthread_mutex_unlock(&(philo->philo_mtx));
	return 0;

}


void life_loop(t_philo *philo)
{
	int run = 1;
	pthread_t pid;
	
	prep_philo(philo);


	pthread_create(&pid, 0, (void *)routine_loop, (void *)philo);
	pthread_detach(pid);



	int alive;
	struct timeval t;

	// gettimeofday(&t, 0),

	alive = 1;
	while (alive)
	{
		gettimeofday(&t, 0);
		if (dies(philo, t) && !(alive = 0))
			p_action(philo, 4);
		// else
		// {
		// 	pthread_mutex_lock(&(philo->contr->stdout));
		// 	ft_putstr("DBG : S= ");
		// 	ft_putnbr_l(t.tv_sec);
		// 	ft_putstr(" : ");
		// 	ft_putnbr_l(t.tv_usec);
		// 	ft_putstr("\n");
		// 	pthread_mutex_unlock(&(philo->contr->stdout));

		// 	// ft_putnbr_l(philo->alive_untill.tv_usec);
		// }
		// pthread_mutex_unlock(&(philo->food_mtx));
	}






	return;
}
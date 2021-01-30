/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/01/30 16:28:31 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	loop(t_philo *phil)
{
	int cpt;

	int testret;

	phil->alive = 1;
	cpt = 0;
	sem_wait(phil->alive_l);
	gettimeofday(&(phil->lmeal), 0);
	sem_post(phil->alive_l);
	testret = 0;
	while (phil->alive && !phil->contr->end)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == phil->contr->must_eat)
		{
			// printf("WE ARE HERE %d %d\n", phil->contr->did_eat, phil->alive);
			testret = 0;
			// phil->contr->did_eat++;
			phil->alive = 0;
			break ;
		}
		print_ts(phil, SLEEP);
		usleep(phil->contr->time_to_sleep * 1000);
	}
	return phil->alive ;
}

char	*modbuf(char *buff, int i)
{
	buff[0] = 'A';
	buff[2] = 0;
	buff[1] = '0' + i;
	return (buff);
}

void	spawn_philos(t_contr *contr)
{
	int			i;
	t_philo		philos[contr->nbr_of_philo];
	char		buff[20];
	pid_t 		forkid[contr->nbr_of_philo];


	i = -1;
	while (++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		philos[i].alive = 1;
		// gettimeofday(&(philos[i].lmeal), 0);
		sem_unlink(modbuf(buff, i));
		philos[i].alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644, 1);
	}
	gettimeofday(&(contr->start), 0);
	sem_unlink("END");
	contr->done = sem_open("END", O_CREAT, 0644, 1);
	i = -1;

	while (++i < contr->nbr_of_philo)
	{
		forkid[i] = fork();
		if (forkid[i] == 0)
		{
			pthread_t tmp;
			pthread_create(&tmp, 0, (void*)life, (void*)&(philos[i]));
			loop(&philos[i]);
			// for (int t = 0; t < 100 * (1 + i); t++)
			// {
			// 	if ( t % 10 == 0)
			// 		printf("loop %d\n",i);
			// 	usleep(5000);
			// }
			// printf("done loop\n");
			// pthread_create(&(pid_tot[1][i]), 0, (void*)life, (void*)&(philos[i]));
			// int ret = loop(&(philos[i]));
			// if (ret == 0)
				// exit(1);
			// while(1)
			// 	usleep(20);
			free(contr->forks);
			return;
		}
		// else
			// printf("phil %d is %d\n", i, forkid[i]);
	}
	i = 0;
	// while ( ++i < contr->nbr_of_philo)
	// {
		// printf("waiting fork\n");
		int ret;
		waitpid(0, &ret, WUNTRACED);

		
		// free(contr->forks);
		for ( int z= 0; z < contr->nbr_of_philo; z++)
		{
			
			kill(forkid[z], SIGINT);
			// sem_close(philos[z].alive_l);
			// sem_close(contr->forks[z]);

		}
		for ( int z= 0; z < contr->nbr_of_philo; z++)
		{
			
			// kill(forkid[z], SIGINT);
			sem_close(philos[z].alive_l);
			sem_close(contr->forks[z]);

		}

		sem_close(contr->done);
		free(contr->forks);
		printf("I KILLED THEM\n");
		// printf("done waiting ret = %d\n",ret);
		// printf("KILL TINE\n");
		// kill(forkid[0], SIGKILL);
		// kill(forkid[1], SIGKILL);
		// kill(forkid[2], SIGKILL);
		// printf("should be dead %d %d\n",i, forkid[i]);
	// }whi
		// usleep(5000000);
		// while (1)
		// 	usleep(50);
}

void	cleanup(t_contr *contr)
{
	int i;

	i = 0;
	while (i < contr->nbr_of_philo)
		sem_close(contr->forks[i++]);
	free(contr->forks);
}

int		main(int argc, char **argv)
{
	t_contr contrn;

	if (argc < 5 || argc > 6)
	{
		write(1,
"nbr of philo | time_to_die | time_to_eat | time_to_sleep | [must eat]\n", 70);
		return (0);
	}
	contr = &contrn;
	if (init_contr(contr, argv, argc))
		return (1);
	spawn_philos(&contrn);

	// printf("THEY ATE %d\n", *(contr->did_eat));

	// if (*(contr->did_eat) == contr->nbr_of_philo)
	// 	write(1, "All philos ate as supposed\n", 27);
	// cleanup(&contrn);
	return (0);
}

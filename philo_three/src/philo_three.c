/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/01/29 17:07:02 by edal--ce         ###   ########.fr       */
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
			testret = 0;
			phil->contr->did_eat++;
			// phil->alive = 0;
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
	pthread_t	pid_tot[2][contr->nbr_of_philo];
	t_philo		philos[contr->nbr_of_philo];
	char		buff[20];


	pid_t 		forkid[contr->nbr_of_philo];


	i = -1;
	gettimeofday(&(contr->start), 0);
	for (int j = 0; j < contr->nbr_of_philo; j++)
	{
		sem_unlink(modbuf(buff, i));
	}
	while (++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		gettimeofday(&(philos[i].lmeal), 0);
		philos[i].alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644);
		forkid[i] = fork();


		if (forkid[i] == 0) // THEY ARE SELF CONTAINED
		{
			pthread_create(&(pid_tot[1][i]), 0, (void*)life, (void*)&(philos[i]));
			int ret = loop(&(philos[i]));
			if (ret == 0)
				exit(1);
			return;
		}

		usleep(50);
	}

	waitpid(-1, 0, WUNTRACED);
	kill(-1, SIGKILL);

	i = 0;
	pid_t status = 1;
	while (status && i < contr->nbr_of_philo)
	{
		int ret = 0;
		printf("waiting\n");
		status = waitpid(-1, &ret, WUNTRACED);
		printf("done waiting\n");
		if (status != 0)
		{
			printf("END OF THE ROAD\n");
			kill(0, SIGKILL);
			break;
		}
	}
	if (status > 0)
		for (int j = 0; j < contr->nbr_of_philo; j++)
		{	
			kill(forkid[j], SIGKILL);
			printf("KILL %d", j);
		}
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

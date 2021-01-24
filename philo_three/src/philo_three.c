/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/01/24 17:19:18 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	loop(t_philo *phil)
{
	int cpt;

	phil->alive = 1;
	cpt = 0;
	sem_wait(phil->alive_l);
	gettimeofday(&(phil->lmeal), 0);
	sem_post(phil->alive_l);
	while (phil->alive && !phil->contr->end)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == phil->contr->must_eat)
		{
			phil->contr->did_eat++;
			phil->alive = 0;
			break ;
		}
		print_ts(phil, SLEEP);
		usleep(phil->contr->time_to_sleep * 1000);
	}
	return ;
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
	while (++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		gettimeofday(&(philos[i].lmeal), 0);
		sem_unlink(modbuf(buff, i));
		philos[i].alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644, 1);
		forkid[i] = fork();
		if (forkid[i] == 0)
		{
			pthread_create(&(pid_tot[1][i]), 0, (void*)life, (void*)&(philos[i]));
			loop(&(philos[i]));
			
			// if (i == 3)
			// 	return;
			exit(1);

			// return;
			
		}
		// pthread_create(&(pid_tot[0][i]), 0, (void*)loop, (void*)&(philos[i]));
		// pthread_create(&(pid_tot[1][i]), 0, (void*)life, (void*)&(philos[i]));
		usleep(50);
	}
	i = -1;
	while (++i < contr->nbr_of_philo)
	{
		int ret = 0;
		waitpid(0, &ret, WUNTRACED);
		// printf("done waiting\n");
		if (WEXITSTATUS(ret))
		{
			// printf("FOUND SOMETHING TO KILL");
			for (int j = 0; j < contr->nbr_of_philo; j++)
			{
				kill(forkid[j], SIGKILL);
			}
			//Murder the other forks
		}
		// pthread_join(pid_tot[0][i], 0);
		// pthread_join(pid_tot[1][i], 0);
		// sem_close(philos[i].alive_l);
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

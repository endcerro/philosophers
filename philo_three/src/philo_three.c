/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/16 20:21:58 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int 		isthisreallife(t_philo *phil)
{
	int t;
	sem_wait(phil->alive_l);
	t = phil->alive;
	sem_post(phil->alive_l);
	if (t == 0)
		return 0;
	sem_wait(contr->done);
	t = contr->end;
	sem_post(contr->done);
	if (t == 1)
		return 0;
	return 1;
}

int			loop(t_philo *phil)
{
	int cpt;
	int ret;

	phil->alive = 1;
	cpt = 0;
	
	// sem_wait(phil->alive_l);
	// gettimeofday(&(phil->lmeal), 0);
	// sem_post(phil->alive_l);
	ret = 2;
	while (isthisreallife(phil))
	{
		printf("ITS REAL\n");
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == contr->must_eat)
		{
			sem_wait(phil->alive_l);
			phil->alive = 0;
			sem_post(phil->alive_l);
			ret = 0;
			// break;
		}
		print_ts(phil, SLEEP);
		usleep(contr->time_to_sleep * 1000);
	}
	printf("ITS NOT\n");
	printf("OH SHIT I DIED\n");
	free(phil->id_str);
	free(contr->forks);
	return (ret);
}

char		*modbuf(char *buff, int i)
{
	buff[0] = 'A';
	buff[2] = 0;
	buff[1] = '0' + i;
	return (buff);
}

t_philo		gphil(int i, char *buff)
{
	t_philo philo;

	philo.id = i;
	philo.alive = 1;
	sem_unlink(modbuf(buff, i));
	philo.alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644, 1);
	philo.id_str = ft_itoa(philo.id + 1);
	gettimeofday(&(philo.lmeal), 0);
	return (philo);
}

void		spawn_philos(char *buff, int i, int ret)
{
	t_philo		philo;
	pid_t		forkid[contr->nbr_of_philo];
	pthread_t	tmp;

	gettimeofday(&(contr->start), 0);
	while (++i < contr->nbr_of_philo)
	{
		forkid[i] = fork();
		if (forkid[i] == 0)
		{
			philo = gphil(i, buff);
			pthread_create(&tmp, 0, (void*)life, (void*)&(philo));
			exit(loop(&philo));
		}
		usleep(50);
	}
	i = -1;
	// waitpidhile (ret != 512 && ++i < contr->nbr_of_philo)
	// {
		// printf("WAITING\n");
		waitpid(-1, &ret, WUNTRACED);
	// }
	write(1, "WAIT DONE\n", 10);
	// i = -1;
	printf("RET IS %d\n",ret );
	if (ret == 512)
		while (++i < contr->nbr_of_philo)
		{
			write(1, "KILLING\n", 8);
			kill(forkid[i], SIGINT);
		}
	else
		write(1, "All philos ate as supposed\n", 27);
}

int			main(int argc, char **argv)
{
	t_contr contrn;
	char	buff[5];

	if (argc < 5 || argc > 6)
	{
		write(1,
"nbr of philo | time_to_die | time_to_eat | time_to_sleep | [must eat]\n", 70);
		return (0);
	}
	contr = &contrn;
	if (init_contr(argv, argc))
		return (1);
	spawn_philos(buff, -1, -1);
	free(contr->forks);
	return (0);
}

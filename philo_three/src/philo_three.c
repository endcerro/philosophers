/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/03 16:11:06 by edal--ce         ###   ########.fr       */
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
	testret = 1;
	while (phil->alive && !contr->end)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == contr->must_eat)
		{
			testret = 0;
			phil->alive = 0;
			return (1);
		}
		print_ts(phil, SLEEP);
		usleep(contr->time_to_sleep * 1000);
	}
	return (2);
}

char	*modbuf(char *buff, int i)
{
	buff[0] = 'A';
	buff[2] = 0;
	buff[1] = '0' + i;
	return (buff);
}

void cleanthatshitup(t_contr *contr)
{
	free(contr->forks);
}

void cleanforks()
{
	int 	i;
	char	buff[20];

	buff[0] = 'F';
	buff[2] = 0;
	i = 0;
	while (i < contr->nbr_of_philo)
	{
		buff[1] = i + '0';
		sem_unlink(buff);
		contr->forks[i] = sem_open(buff, O_CREAT, 0644, 1);
		i++;
	}
}

t_philo gphil(int i, char *buff)
{
	t_philo philo;

	philo.id = i;
	philo.alive = 1;
	sem_unlink(modbuf(buff, i));
	philo.alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644, 1);

	return (philo);
}


void	spawn_philos()
{
	int			i;
	t_philo		philo;
	char		buff[20];
	pid_t 		forkid[contr->nbr_of_philo];
	pthread_t 	tmp;
	int 		ret;
	int 		j;

	j = 0;
	i = ret =-1;
	buff[0] = 0;
	gettimeofday(&(contr->start), 0);
	while (++i < contr->nbr_of_philo)
	{
		philo = gphil(i, buff);
		forkid[i] = fork();
		if (forkid[i] == 0)
		{
			pthread_create(&tmp, 0, (void*)life, (void*)&(philo));
			exit (loop(&philo));
		}
	}
	i = -1;

	while (ret != 512 && j < contr->nbr_of_philo)
	{
		waitpid(0, &ret, WUNTRACED);
		j++;
	}
	if (ret == 512)
		while (++i < contr->nbr_of_philo)
			kill(forkid[i], SIGINT);
	else
		write(1, "All philos ate as supposed\n", 27);
	cleanthatshitup(contr);
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
	if (init_contr(argv, argc))
		return (1);
	spawn_philos();
	return (0);
}

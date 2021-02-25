/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/25 16:34:14 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			loop(t_philo *phil)
{
	int cpt;
	int ret;

	phil->alive = 1;
	cpt = 0;
	sem_wait(phil->alive_l);
	gettimeofday(&(phil->lmeal), 0);
	sem_post(phil->alive_l);
	ret = 2;
	while (isthisreallife(phil))
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == contr->must_eat)
		{
			sem_wait(phil->alive_l);
			phil->alive = 0;
			sem_post(phil->alive_l);
			ret = 0;
			break ;
		}
		print_ts(phil, SLEEP);
		usleep(contr->time_to_sleep * 1000);
	}
	return (ret);
}

t_philo		gphil(int i, char *buff)
{
	t_philo philo;
	char	*tmp;

	philo.id = i;
	philo.alive = 1;
	sem_unlink(modbuf(buff, i));
	philo.alive_l = sem_open(modbuf(buff, i), O_CREAT, 0644, 1);
	tmp = ft_itoa(philo.id + 1);
	philo.id_str[0] = 0;
	ft_strlcat(philo.id_str, tmp);
	free(tmp);
	return (philo);
}

void		prep()
{
	// int i;

	// i = -1;
	// buff[0] = 'f';
	// buff[2] = 0;
	// while (++i < contr->nbr_of_philo)
	// {
	// 	buff[1] = i + '0';
	// 	sem_unlink(buff);
	sem_unlink("FORKS");
	contr->forks = sem_open("FORKS", O_CREAT, 0644, contr->nbr_of_philo);
	// }
	gettimeofday(&(contr->start), 0);
}

void		spawn_philos(char *buff, int i, int ret)
{
	t_philo		philo;
	pid_t		forkid[contr->nbr_of_philo];
	pthread_t	tmp;
	// sem_t		*sems[contr->nbr_of_philo + 1];

	// contr->forks = (sem_t **)&sems;
	prep();
	while (++i < contr->nbr_of_philo)
	{
		forkid[i] = fork();
		if (forkid[i] == 0)
		{
			philo = gphil(i, buff);
			pthread_create(&tmp, 0, (void*)life, (void*)&(philo));
			exit(loop(&philo));
			// exit(0);
		}
		// usleep(50);
	}
	i = -1;
	while (ret != 512 && ++i < contr->nbr_of_philo)
		waitpid(-1, &ret, WUNTRACED);
	if (ret == 512)
		while (++i < contr->nbr_of_philo)
			kill(forkid[i], SIGINT);
	else
		write(1, "All philos ate as supposed\n", 27);
}

int			main(int argc, char **argv)
{
	t_contr contrn;
	char	buff[10];

	if (argc < 5 || argc > 6)
	{
		write(1,
"nbr of philo | time_to_die | time_to_eat | time_to_sleep | [must eat]\n", 70);
		return (0);
	}
	contr = &contrn;
	buff[0] = 0;
	if (init_contr(argv, argc))
		return (1);
	spawn_philos(buff, -1, -1);
	sem_close(contr->forks);
	return (0);
}

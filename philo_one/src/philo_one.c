/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/25 15:00:52 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	loop(t_philo *phil)
{
	int cpt;

	phil->alive = 1;
	cpt = 0;
	gettimeofday(&(phil->lmeal), 0);
	while (phil->alive && !contr->end)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == contr->must_eat)
		{
			contr->did_eat++;
			phil->alive = 0;
			break ;
		}
		print_ts(phil, SLEEP);
		usleep(contr->time_to_sleep * 1000);
	}
	pthread_mutex_destroy(&(phil->alive_l));
	return ;
}

void	spawn_philos(void)
{
	int			i;
	pthread_t	pid[contr->nbr_of_philo];
	pthread_t	pid_l[contr->nbr_of_philo];
	t_philo		philos[contr->nbr_of_philo];

	i = -1;
	gettimeofday(&(contr->start), 0);
	while (++i < contr->nbr_of_philo)
	{
		philos[i].contr = contr;
		philos[i].id = i;
		char *tmp = ft_itoa(i);
		philos[i].idstr[0] = 0;
		ft_strlcat(philos[i].idstr, tmp);
		free(tmp);
		pthread_mutex_init(&(philos[i].alive_l), 0);
		pthread_create(&(pid[i]), 0, (void*)loop, (void*)&(philos[i]));
		pthread_create(&(pid_l[i]), 0, (void*)life, (void*)&(philos[i]));
		usleep(50);
	}
	i = -1;
	while (++i < contr->nbr_of_philo)
		pthread_join(pid_l[i], 0);
	if (contr->did_eat == contr->nbr_of_philo)
		write(1, "All philos ate as supposed\n", 27);
}

void	cleanup(void)
{
	int i;

	i = 0;
	while (i < contr->nbr_of_philo)
		pthread_mutex_destroy(&(contr->forks[i++]));
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
	if (init_contr(argv, argc))
		return (1);
	spawn_philos();
	cleanup();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/27 16:24:41 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	loop(t_philo *phil)
{
	int			cpt;
	pthread_t	pid;

	cpt = 0;
	while (!contr->run)
		;
	pthread_create(&pid, 0, (void*)life, (void*)phil);
	while (phil->alive && contr->run)
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
		zzz(contr->time_to_sleep * 1000);
	}
	return ;
}

int		prep_philos(t_philo *philos)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < contr->nbr_of_philo)
	{
		philos[i].id = i;
		philos[i].alive = 1;
		philos[i].idstr[0] = 0;
		tmp = ft_itoa(i + 1);
		ft_strlcat(philos[i].idstr, tmp);
		free(tmp);
		pthread_mutex_init(&(philos[i].alive_l), 0);
	}
	return (0);
}

void	spawn_philos(void)
{
	int			i;
	pthread_t	pid[contr->nbr_of_philo];
	t_philo		philos[contr->nbr_of_philo];

	i = 0;
	prep_philos(philos);
	contr->run = 0;
	i = -1;
	while (++i < contr->nbr_of_philo)
		pthread_create(&(pid[i]), 0, (void*)loop, (void*)&(philos[i]));
	contr->start = g_ms();
	contr->run = 1;
	i = -1;
	while (++i < contr->nbr_of_philo)
	{
		pthread_join(pid[i], 0);
		pthread_mutex_destroy(&(philos[i].alive_l));
	}
	if (contr->did_eat == contr->nbr_of_philo)
		write(1, "All philos ate as supposed\n", 27);
}

void	cleanup(void)
{
	int i;

	i = 0;
	while (i < contr->nbr_of_philo)
		pthread_mutex_destroy(&(contr->forks[i++]));
	pthread_mutex_destroy(&contr->out);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:14:58 by edal              #+#    #+#             */
/*   Updated: 2021/02/28 15:49:11 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	loop(t_philo *phil)
{
	int			cpt;

	cpt = 0;
	while (phil->alive && contr->run)
	{
		print_ts(phil, THINK);
		eat(phil);
		if (++cpt == contr->must_eat)
		{
			phil->alive = 0;
			break ;
		}
		print_ts(phil, SLEEP);
		zzz(contr->time_to_sleep * 1000);
	}
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
		sem_unlink(tmp);
		philos[i].alive_l = sem_open(tmp, O_CREAT, 0644, 1);
		free(tmp);
	}
	return (0);
}

void	spawn_philos(void)
{
	int			i;
	pid_t		pid[contr->nbr_of_philo];
	t_philo		philos[contr->nbr_of_philo];
	int			ret;

	prep_philos(philos);
	contr->start = g_ms();
	contr->run = 1;
	ret = 0;
	i = -1;
	while (++i < contr->nbr_of_philo)
		if ((pid[i] = fork()) == 0)
			exit(life(&philos[i]));
	i = -1;
	while (ret != 512 && ++i < contr->nbr_of_philo)
	{
		waitpid(-1, &ret, WUNTRACED);
		sem_close(philos[i].alive_l);
	}
	i = -1;
	if (ret == 512)
		while (++i < contr->nbr_of_philo)
			kill(pid[i], SIGINT);
	else
		write(1, "All philos ate as supposed\n", 27);
}

void	cleanup(void)
{
	int i;

	i = -1;
	while (++i < contr->nbr_of_philo)
		sem_post(contr->forks);
	sem_close(contr->out);
	sem_close(contr->forks);
}

int		main(int argc, char **argv)
{
	t_contr contrn;

	contr = &contrn;
	if (argc < 5 || argc > 6)
	{
		write(1,
"nbr of philo | time_to_die | time_to_eat | time_to_sleep | [must eat]\n", 70);
		return (0);
	}
	if (init_contr(argv, argc))
	{
		write(1, "Invalid launch sequence\n", 24);
		return (1);
	}
	spawn_philos();
	sem_close(contr->forks);
	return (0);
}

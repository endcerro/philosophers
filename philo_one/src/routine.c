/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/28 16:23:29 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	life(t_philo *phil)
{
	long	delta;

	phil->t = g_ms();
	while (phil->alive && contr->run)
	{
		pthread_mutex_lock(&(phil->alive_l));
		delta = g_ms();
		if (delta - phil->t >= contr->time_to_die)
		{
			print_ts(phil, DIE);
			contr->run = 0;
			pthread_mutex_unlock(&(phil->alive_l));
			break ;
		}
		pthread_mutex_unlock(&(phil->alive_l));
		usleep(100);
	}
	phil->alive = 0;
}

long	g_ms(void)
{
	long			ms;
	struct timeval	t;

	ms = 0;
	gettimeofday(&t, 0);
	ms = t.tv_sec * 1000;
	ms += t.tv_usec / 1000;
	return (ms);
}

int		eat(t_philo *phil)
{
	int id;
	int one;
	int two;

	id = phil->id;
	one = (!(id % 2)) ? id + 1 : id;
	two = (!(id % 2)) ? id : id - 1;
	pthread_mutex_lock(&(contr->forks[one]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(contr->forks[two]));
	print_ts(phil, FORK);
	pthread_mutex_lock(&(phil->alive_l));
	print_ts(phil, EAT);
	phil->t = g_ms();
	pthread_mutex_unlock(&(phil->alive_l));
	zzz(contr->time_to_eat * 1000);
	pthread_mutex_unlock(&(contr->forks[one]));
	pthread_mutex_unlock(&(contr->forks[two]));
	return (0);
}

void	print_ac(char *buff, int action, int len)
{
	if (action == FORK)
		x_memcpy(buff, " has taken a fork\n", len);
	else if (action == EAT)
		x_memcpy(buff, " is eating\n", len);
	else if (action == SLEEP)
		x_memcpy(buff, " is sleeping\n", len);
	else if (action == THINK)
		x_memcpy(buff, " is thinking\n", len);
	else if (action == DIE)
		x_memcpy(buff, " died\n", len);
	pthread_mutex_lock(&contr->out);
	if (contr->run)
		write(1, buff, ft_strlen(buff));
	pthread_mutex_unlock(&contr->out);
}

void	print_ts(t_philo *phil, int action)
{
	long	ms;
	char	buff[1000];
	int		len;

	if (!contr->run)
		return ;
	ms = g_ms() - contr->start;
	digit(buff, ms, 0, getlen(ms) - 1);
	len = ft_strlen(buff);
	x_memcpy(buff, "ms\t ", len);
	len += 4;
	x_memcpy(buff, "ms\t ", len);
	digit(buff, phil->id + 1, len, getlen(phil->id + 1) - 1);
	len += getlen(phil->id + 1);
	print_ac(buff, action, len);
}

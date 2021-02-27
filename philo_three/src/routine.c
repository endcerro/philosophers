/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:59:10 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/27 15:30:44 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	zzz(long d)
{
	struct timeval	tmp;
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&tmp, NULL);
		if ((((long)(tmp.tv_sec - start.tv_sec)) * 1000000 +
		((long)(tmp.tv_usec - start.tv_usec))) >= d)
			return ;
	}
}

int		life(t_philo *phil)
{
	long		delta;
	pthread_t	pid;
	int			ret;

	ret = 0;
	pid = 0;
	pthread_create(&pid, 0, (void*)loop, (void*)phil);
	phil->t = g_ms();
	while (phil->alive && contr->run)
	{
		delta = g_ms();
		if (delta - phil->t >= contr->time_to_die)
		{
			print_ts(phil, DIE);
			contr->run = 0;
			ret = 2;
			break ;
		}
	}
	phil->alive = 0;
	return (ret);
}

int		eat(t_philo *phil)
{
	sem_wait(contr->forks);
	print_ts(phil, FORK);
	sem_wait(contr->forks);
	print_ts(phil, FORK);
	print_ts(phil, EAT);
	phil->t = g_ms();
	zzz(contr->time_to_eat * 1000);
	sem_post(contr->forks);
	sem_post(contr->forks);
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
	{
		x_memcpy(buff, " died\n", len);
	}
	sem_wait(contr->out);
	if (contr->run)
	{
		write(1, buff, ft_strlen(buff));
		sem_post(contr->out);
	}
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

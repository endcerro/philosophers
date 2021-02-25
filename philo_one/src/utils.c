/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/02/26 00:16:40 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int		init_contr(char **argv, int argc)
{
	int i;

	i = 0;
	contr->nbr_of_philo = ft_atoi(argv[1]);
	contr->time_to_die = ft_atoi(argv[2]);
	contr->time_to_eat = ft_atoi(argv[3]);
	contr->time_to_sleep = ft_atoi(argv[4]);
	contr->must_eat = -1;
	contr->end = 0;
	contr->did_eat = 0;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	if (!(contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo)))
		return (1);
	while (i < contr->nbr_of_philo)
		pthread_mutex_init(&(contr->forks[i++]), 0);
	pthread_mutex_init(&(contr->out), 0);
	return (0);
}

void	print_ac(char *buff, int action, int len)
{

	if (action == FORK)
		x_memcpy(buff," has taken a fork\n", len);
	else if (action == EAT)
		x_memcpy(buff, " is eating\n", len);
	else if (action == SLEEP)
		x_memcpy(buff, " is sleeping\n", len);
	else if (action == THINK)
		x_memcpy(buff, " is thinking\n", len);
	else if (action == DIE)
		x_memcpy(buff, " died\n",len);
	pthread_mutex_lock(&contr->out);
	if (contr->run)
		write(1, buff, ft_strlen(buff));	
	pthread_mutex_unlock(&contr->out);

}
 	
void	print_ts(t_philo *phil, int action)
{
	long	ms;
	char	buff[1000];

	if (!contr->run)
		return;
	ms =  g_ms() - contr->start;
	digit(buff, ms, 0, getlen(ms) - 1);
	int len = ft_strlen(buff);
	x_memcpy(buff, "ms\t ", len);
	len += 4;
	x_memcpy(buff, "ms\t ", len);
	digit(buff, phil->id + 1, len, getlen(phil->id + 1) - 1);
	len += getlen(phil->id + 1);
	print_ac(buff, action, len);
}

int		ft_atoi(const char *in)
{
	int pos;
	int nb;

	nb = 0;
	pos = 1;
	while (*in == ' ' || *in == '	' || *in == '\n'
		|| *in == '\t' || *in == '\v' || *in == '\f' || *in == '\r')
		in++;
	if (*in == '-' && (pos = -1))
		in++;
	else if (*in == '+')
		in++;
	while (*in < 58 && *in > 47)
		nb = nb * 10 + (*(in++) - '0');
	return (nb * pos);
}

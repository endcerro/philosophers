/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/01/10 17:23:32 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void	init_contr(t_contr *contr, char **argv, int argc)
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
	contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo);
	while (i < contr->nbr_of_philo)
		pthread_mutex_init(&(contr->forks[i++]), 0);
}

void	print_ac(char *buff, int action)
{
	if (action == FORK)
		ft_strlcat(buff, " has taken a fork\n", 1000);
	else if (action == EAT)
		ft_strlcat(buff, " is eating\n", 1000);
	else if (action == SLEEP)
		ft_strlcat(buff, " is sleeping\n", 1000);
	else if (action == THINK)
		ft_strlcat(buff, " is thinking\n", 1000);
	else if (action == DIE)
		ft_strlcat(buff, " died\n", 1000);
	write(1, buff, ft_strlen(buff));
}

void	print_ts(t_philo *phil, int action)
{
	struct timeval	delta;
	unsigned long	ms;
	char			buff[1000];
	char			*tmp;

	gettimeofday(&delta, 0);
	ms = delta.tv_sec * 1000000;
	ms += delta.tv_usec;
	ms -= phil->contr->start.tv_sec * 1000000 + phil->contr->start.tv_usec;
	ms = ms / 1000;
	buff[0] = 0;
	tmp = ft_itoa(ms);
	ft_strlcat(buff, tmp, 1000);
	free(tmp);
	ft_strlcat(buff, "ms ", 1000);
	tmp = ft_itoa((unsigned long)phil->id);
	ft_strlcat(buff, tmp, 1000);
	free(tmp);
	if (phil->alive == 0 || phil->contr->end)
		return ;
	print_ac(buff, action);
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

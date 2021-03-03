/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/02/28 15:51:58 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			init_contr(char **argv, int argc)
{
	int		i;

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
	if ( contr->nbr_of_philo <= 0 || contr->nbr_of_philo >= 200 ||
		contr->time_to_eat <= 0 || contr->time_to_die <= 0 ||
		contr->time_to_sleep <= 0 ||
		(contr->must_eat != -1 && contr->must_eat <= 0))
		return (1);
	if (!(contr->forks = malloc(sizeof(pthread_mutex_t) * contr->nbr_of_philo)))
		return (1);
	while (i < contr->nbr_of_philo)
		pthread_mutex_init(&(contr->forks[i++]), 0);
	pthread_mutex_init(&(contr->out), 0);
	return (0);
}

void		digit(char buff[1000], long n, int pos, int len)
{
	if (!n)
		buff[pos] = '0';
	buff[pos + len + 1] = 0;
	while (n)
	{
		buff[pos + len] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

void		zzz(long d)
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

void		x_memcpy(char *dst, char *src, int index)
{
	int i;

	i = -1;
	while (src[++i])
		dst[index + i] = src[i];
	dst[index + i] = 0;
}

int			ft_atoi(const char *in)
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

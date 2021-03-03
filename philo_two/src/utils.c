/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/02/28 15:54:23 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	int		i;

	i = 0;
	contr->nbr_of_philo = ft_atoi(argv[1]);
	contr->time_to_die = ft_atoi(argv[2]);
	contr->time_to_eat = ft_atoi(argv[3]);
	contr->time_to_sleep = ft_atoi(argv[4]);
	contr->must_eat = -1;
	contr->did_eat = 0;
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
	if (contr->nbr_of_philo <= 0 || contr->nbr_of_philo >= 200 ||
		contr->time_to_eat <= 0 || contr->time_to_die <= 0 ||
		contr->time_to_sleep <= 0 ||
		(contr->must_eat != -1 && contr->must_eat <= 0))
		return (1);
	sem_unlink("FORKS");
	sem_unlink("OUT");
	contr->forks = sem_open("FORKS", O_CREAT, 0644, contr->nbr_of_philo);
	contr->out = sem_open("OUT", O_CREAT, 0644, 1);
	return (0);
}

int		getlen(long nb)
{
	int length;

	length = (!nb) ? 1 : 0;
	while (nb)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

void	x_memcpy(char *dst, char *src, int index)
{
	int i;

	i = -1;
	while (src[++i])
		dst[index + i] = src[i];
	dst[index + i] = 0;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/02/25 22:38:00 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	g_ms(void)
{
	long			ms;
	struct timeval	t;

	ms = 0;
	while (gettimeofday(&t, 0) == -1)
		printf("TOD_ERR\n");
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
	return (0);
}

void	print_ac(char *buff, int action)
{
	if (action == FORK)
		ft_strlcat(buff, " has taken a fork\n");
	else if (action == EAT)
		ft_strlcat(buff, " is eating\n");
	else if (action == SLEEP)
		ft_strlcat(buff, " is sleeping\n");
	else if (action == THINK)
		ft_strlcat(buff, " is thinking\n");
	else if (action == DIE)
		ft_strlcat(buff, " died\n");
	write(1, buff, ft_strlen(buff));
}
 	
void	print_ts(t_philo *phil, int action)
{
	

	long ms = g_ms() - contr->start;


	// struct timeval	delta;
	// unsigned long	ms;
	char			buff[1000];
	char			*tmp;

	// gettimeofday(&delta, 0);
	// ms = delta.tv_sec * 1000 + delta.tv_usec / 1000;
	// ms -= contr->start.tv_sec * 1000 + contr->start.tv_usec / 1000;
	// // ms = ms / 1000;
	buff[0] = 0;
	tmp = ft_itoa(ms);
	// printf("MS = %ld\n",ms );
	ft_strlcat(buff, tmp);
	free(tmp);
	ft_strlcat(buff, "ms ");
	ft_strlcat(buff, phil->idstr);
	if (phil->alive == 0 || contr->end)
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

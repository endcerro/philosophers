/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/02/25 16:34:54 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

char	*modbuf(char *buff, int i)
{
	buff[0] = 'A';
	buff[2] = 0;
	buff[1] = '0' + i;
	return (buff);
}

int		init_contr(char **argv, int argc)
{
	int		i;
	char	buff[20];

	buff[0] = 'F';
	buff[2] = 0;
	contr->nbr_of_philo = ft_atoi(argv[1]);
	contr->time_to_die = ft_atoi(argv[2]);
	contr->time_to_eat = ft_atoi(argv[3]);
	contr->time_to_sleep = ft_atoi(argv[4]);
	contr->must_eat = -1;
	contr->end = 0;
	i = 0;
	sem_unlink("END");
	contr->done = sem_open("END", O_CREAT, 0644, 1);
	if (argc == 6)
		contr->must_eat = ft_atoi(argv[5]);
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
	struct timeval	delta;
	unsigned long	ms;
	char			buff[1000];
	char			*tmp;

	gettimeofday(&delta, 0);
	ms = delta.tv_sec * 1000000 + delta.tv_usec;
	ms -= contr->start.tv_sec * 1000000 + contr->start.tv_usec;
	ms /= 1000;
	buff[0] = 0;
	tmp = ft_itoa(ms);
	ft_strlcat(buff, tmp);
	free(tmp);
	ft_strlcat(buff, "ms ");
	ft_strlcat(buff, phil->id_str);
	if ((phil->alive == 1 && contr->end == 0))
		print_ac(buff, action);
	if (action == DIE)
		exit(2);
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

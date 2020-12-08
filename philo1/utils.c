/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2020/12/07 21:55:01 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void print_ts(t_philo *phil, int action)
{
	struct timeval delta;
	unsigned long ms;


	gettimeofday(&delta, 0);	
	
	ms = delta.tv_sec * 1000;
	ms += delta.tv_usec / 100;
	ms -= phil->contr->start.tv_sec * 1000;
	ms -= phil->contr->start.tv_usec / 1000;

	pthread_mutex_lock(&(phil->contr->stdout));

	ft_putnbr_l(ms);
	write(1," ", 1);
	ft_putnbr(phil->id);

	if (action == FORK)
		ft_putstr(" has taken a fork\n");
	else if (action == EAT)	
		ft_putstr(" is eating\n");
	else if (action == SLEEP)
		ft_putstr(" is sleeping\n");
	else if (action == THINK)
		ft_putstr(" is thinking\n");
	else if (action == DIE)
		ft_putstr(" died\n");

	pthread_mutex_unlock(&(phil->contr->stdout));

	// return (0);
}


void print(char *str, t_contr *contr)
{
	pthread_mutex_lock(&(contr->stdout));
	ft_putstr(str);
	pthread_mutex_unlock(&(contr->stdout));
}

void print_nb(char *str, int i, t_contr *contr)
{
	pthread_mutex_lock(&(contr->stdout));
	ft_putstr(str);
	ft_putnbr(i);
	write(1,"\n",1);
	pthread_mutex_unlock(&(contr->stdout));
}




int	ft_atoi(const char *in)
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

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putnbr_l(unsigned long n)
{
	char tmp[2];
	
	tmp[1] = 0;
	if (n >= 10)
	{
		ft_putnbr_l(n / 10);
		tmp[0] = n % 10 + '0';
	}
	else
		tmp[0] = n + '0';
	ft_putstr(tmp);
}


void	ft_putunbr(unsigned int n)
{
	char tmp[2];
	tmp[1] = 0;

	if (n >= 10)
	{
		ft_putunbr(n / 10);
		tmp[0] = n % 10 + '0';
		ft_putstr(tmp);
	}
	else
	{
		tmp[0] = n + '0';
		ft_putstr(tmp);
	}
}

void	ft_putnbr(int n)
{
	char tmp[2];
	tmp[1] = 0;
	if (n < 0)
	{
		printf("NEG VALUE : %d\n",n);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		tmp[0] = n % 10 + '0';
		ft_putstr(tmp);
	}
	else
	{
		tmp[0] = n + '0';
		ft_putstr(tmp);
	}
}
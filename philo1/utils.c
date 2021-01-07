/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:43 by edal              #+#    #+#             */
/*   Updated: 2021/01/07 17:57:55 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo1.h"

void print_ts(t_philo *phil, int action)
{
	struct timeval delta;
	unsigned long ms;
	char buff[1000];

	gettimeofday(&delta, 0);		
	ms = delta.tv_sec * 1000;
	ms += delta.tv_usec / 100;
	ms -= phil->contr->start.tv_sec * 1000;
	ms -= phil->contr->start.tv_usec / 1000;


	// pthread_mutex_lock(&(phil->contr->stdout));
	buff[0] = 0;
	char *tmp;

	tmp = ft_itoa(ms);
	
	ft_strlcat(buff, tmp, 1000);
	free(tmp);
	ft_strlcat(buff, " ", 1000);

	tmp = ft_itoa((unsigned long)phil->id);
	
	ft_strlcat(buff, tmp, 1000);
	free(tmp);
	
	if (action == FORK)
		ft_strlcat(buff," has taken a fork\n",1000);
	else if (action == EAT)
		ft_strlcat(buff," is eating\n", 1000);
	else if (action == SLEEP)
		ft_strlcat(buff," is sleeping\n", 1000);
	else if (action == THINK)
		ft_strlcat(buff, " is thinking\n", 1000);
	else if (action == DIE)
		ft_strlcat(buff, " died\n", 1000);
	write(1, buff, ft_strlen(buff));
	// pthread_mutex_unlock(&(phil->contr->stdout));

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
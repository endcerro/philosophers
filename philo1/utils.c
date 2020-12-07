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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:10:15 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/25 21:58:30 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, char *src)
{
	int i;
	int posdst;

	posdst = 0;
	while (dst[posdst])
		posdst++;
	i = -1;
	while (src[++i])
		dst[posdst + i] = src[i];
	dst[posdst + i] = 0;
	return (0);
}

unsigned long	getlen(unsigned long n)
{
	unsigned long		i;

	i = 1;
	if (n < 0)
		i++;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

unsigned long	ft_pow(unsigned long nb, unsigned long pow)
{
	unsigned long		i;
	unsigned long		dest;

	dest = 1;
	i = 0;
	while (++i < pow)
		dest = dest * nb;
	return (dest);
}

char			*ft_itoa(unsigned long n)
{
	char				*out;
	unsigned long		len;
	unsigned long		i;
	unsigned long		indxo;

	indxo = 0;
	i = 0;
	len = getlen(n);
	if (!(out = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		out[indxo++] = (n / ft_pow(10, len - i)) + '0';
		n -= n / ft_pow(10, len - i) * ft_pow(10, len - i);
		i++;
	}
	out[indxo] = 0;
	return (out);
}

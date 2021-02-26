/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:10:15 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/26 15:49:57 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void			digit(char buff[1000], long n, int pos, int len)
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

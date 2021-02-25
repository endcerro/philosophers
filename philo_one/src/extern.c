/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:10:15 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/26 00:33:43 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int	getlen(long nb)
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

long	ft_pow(long nb, long pow)
{
	long		i;
	long		dest;

	dest = 1;
	i = 0;
	while (++i < pow)
		dest = dest * nb;
	return (dest);
}

char			*ft_itoa(long n)
{
	char				*out;
	long		len;
	long		i;
	long		indxo;

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

void	digit(char buff[1000], long n, int pos, int len)
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
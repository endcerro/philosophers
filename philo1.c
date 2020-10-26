/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 18:28:08 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 19:14:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

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


typedef struct m_contr
{	
	unsigned int 	nbr;
	unsigned int 	die;
	unsigned int 	eat;
	unsigned int 	sleep;
	int 			m_eat;

} t_contr;

void *memes(void *param)
{
	int id = (int)param;
	int cpt = 0;
	while (cpt < 100)
	{
		printf("Hello i am philo number %d and this is %d\n", id, cpt++);
		usleep(10000);
	}
	return (0);
}

void printinit(t_contr *contr)
{
	printf("Ammount of philos : %d\n",contr->nbr);
	printf("Time to die : %d\n",contr->die);
	printf("Time to eat : %d\n",contr->eat);
	printf("Time to sleep : %d\n",contr->sleep);
	printf("Must eat : %d\n",contr->m_eat);
}

void spawn_philo()
{
	pthread_t pid;
	pthread_create(&pid, 0, &memes, (void *)1);
	pthread_join(pid, NULL);
}


int init(int argc, char **argv, t_contr *contr)
{
	if (argc < 5 || argc > 6)
	{
		printf("ERROR ARG COUNT\n");
		return (1);
	}
	contr->nbr = (unsigned int)ft_atoi(argv[1]);
	contr->die = (unsigned int)ft_atoi(argv[2]);
	contr->eat = (unsigned int)ft_atoi(argv[3]);
	contr->sleep = (unsigned int)ft_atoi(argv[4]);
	contr->m_eat = -1;
	if (argc == 6)
		contr->m_eat = ft_atoi(argv[5]);
	// printinit(contr);
	return (0);
}


int main(int argc, char **argv)
{
	t_contr contr;

	// if (init(argc, argv, &contr))
		// return (1);
	spawn_philo();
	return (0);
}
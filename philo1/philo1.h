/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2020/11/01 18:56:03 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO1_H
# define PHILO1_H

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct m_test
{	
	int 			id;
	pthread_mutex_t *mutex;
	pthread_mutex_t *check;
	int 			*lock;

} t_test;

typedef struct m_contr
{	
	unsigned int 	nbr_of_philo;
	unsigned int 	time_to_die;
	unsigned int 	time_to_eat;
	unsigned int 	time_to_sleep;
	int 			must_eat;
	pthread_mutex_t mutex;
	int lock;

	int 			*forks;

	int 			print_lock;

} t_contr;

int	ft_atoi(const char *in);
void ft_putstr(char *str);
int ft_strlen(char *str);
void printinit(t_contr *contr);

#endif
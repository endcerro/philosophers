/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                l    +:+ +:+         +:+     */
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
	unsigned long 	time_to_die;
	unsigned int 	time_to_eat;
	unsigned int 	time_to_sleep;
	int 			must_eat;
	pthread_mutex_t mutex[2];


	pthread_mutex_t stdout;


	int lock;


	struct timeval	start;
	int 			*forks;

	int 			print_lock;

} t_contr;

typedef struct m_philo
{
	int 			id;
	int 			alive;
	pthread_mutex_t alive_mtx;
	pthread_mutex_t food_mtx;

	pthread_mutex_t forks[2];

	t_contr *contr;

	unsigned long ttdie;

	pthread_mutex_t philo_mtx;

	struct timeval	ate;


	struct timeval  alive_untill;

} t_philo;



int	ft_atoi(const char *in);
void ft_putstr(char *str);
int ft_strlen(char *str);
void printinit(t_contr *contr);
void	ft_putnbr(int n);
void	ft_putnbr_l(long int n);

#endif
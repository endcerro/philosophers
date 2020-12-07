/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2020/12/07 21:55:12 by edal             ###   ########.fr       */
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

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIE 4


typedef struct m_contr
{	
	int 	nbr_of_philo;		
	unsigned long 	time_to_die;		//In miliseconds
	unsigned int 	time_to_eat;		//In miliseconds
	unsigned int 	time_to_sleep;		//In miliseconds

	pthread_mutex_t stdout;


	pthread_mutex_t *forks;



	struct timeval	start;
} t_contr;


typedef struct m_philo
{
	int 			id;
	int 			alive;
	struct timeval 	lmeal;

	pthread_mutex_t lock;

	t_contr *contr;
	
} t_philo;



/* UTILS */ 

int	ft_atoi(const char *in);
void ft_putstr(char *str);
int ft_strlen(char *str);
void	ft_putnbr(int n);
void	ft_putunbr(unsigned int n);
void	ft_putnbr_l(unsigned long n);

#endif
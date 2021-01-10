/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2021/01/10 14:09:27 by edal--ce         ###   ########.fr       */
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
	int 			nbr_of_philo;		
	int 		 	time_to_die;		//In miliseconds
	int 		 	time_to_eat;		//In miliseconds
	int 			time_to_sleep;		//In miliseconds
	int 			must_eat;	
	char 			end;

	pthread_mutex_t *forks;				//mutex array for forks
	struct timeval	start;				//Start of the program
} t_contr;


typedef struct m_philo
{
	int 			id;					//ID
	int 			alive;				//Bool alive ?
	struct timeval 	lmeal;				//Last meal, update when eat
	pthread_mutex_t alive_l;
	pthread_mutex_t lock;				//Lock on the phil, check alive

	t_contr *contr;						//Ref to contr
	
} t_philo;

t_contr			*contr;


/* PHILO TOOLS */
void init_contr(t_contr *contr, char **argv, int argc);
void print_ts(t_philo *phil, int action);
void print(char *str, t_contr *contr);
void print_nb(char *str, int i, t_contr *contr);

/* UTILS */ 

int		ft_atoi(const char *in);
void 	ft_putstr(char *str);
int 	ft_strlen(char *str);
void	ft_putnbr(int n);
void	ft_putunbr(unsigned int n);
void	ft_putnbr_l(unsigned long n);
char			*ft_itoa(unsigned long n);
size_t	ft_strlcat(char *dst,char *src, size_t size);

#endif
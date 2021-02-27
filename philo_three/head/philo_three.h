/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/27 16:19:28 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef	struct		s_contr
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	sem_t			*out;
	sem_t			*forks;
	long			start;
	int				run;
}					t_contr;
typedef	struct		s_philo
{
	char			idstr[20];
	int				id;
	int				alive;
	long			t;
	sem_t			*alive_l;
}					t_philo;

struct s_contr		*contr;
int					init_contr(char **argv, int argc);
void				print_ts(t_philo *phil, int action);
int					life(t_philo *phil);
int					eat(t_philo *phil);
int					check_alive(t_philo *phil);
int					ft_atoi(const char *in);
int					ft_strlen(char *str);
char				*ft_itoa(unsigned long n);
size_t				ft_strlcat(char *dst, char *src);
int					isthisreallife(t_philo *phil);
char				*modbuf(char *buff, int i);
void				loop(t_philo *phil);
long				g_ms(void);
void				x_memcpy(char *dst, char *src, int index);
void				digit(char buff[1000], long n, int pos, int len);
int					getlen(long nb);
void				zzz(long d);

#endif

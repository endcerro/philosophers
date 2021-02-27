/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/27 13:32:11 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
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
	int				did_eat;
	sem_t			*forks;
	sem_t			*out;
	long			start;
	int				run;
}					t_contr;
typedef	struct		s_philo
{
	int				id;
	int				alive;
	long			t;
	char			idstr[20];
}					t_philo;

struct s_contr		*contr;
int					init_contr(char **argv, int argc);
void				print_ts(t_philo *phil, int action);
void				life(t_philo *phil);
int					eat(t_philo *phil);
int					check_alive(t_philo *phil);
int					ft_atoi(const char *in);
int					ft_strlen(char *str);
char				*ft_itoa(unsigned long n);
size_t				ft_strlcat(char *dst, char *src);
void				zzz(long d);
void				x_memcpy(char *dst, char *src, int index);
void				digit(char buff[1000], long n, int pos, int len);
int					getlen(long nb);
long				g_ms(void);
void				loop(t_philo *phil);

#endif

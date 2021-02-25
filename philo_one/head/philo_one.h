/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal <edal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2021/02/25 23:22:17 by edal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
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
	char			end;
	pthread_mutex_t *forks;
	pthread_mutex_t out;
	long 			start;
	int 			run;
}					t_contr;

typedef	struct		s_philo
{
	long 			t[2];
	int				id;
	int				alive;
	long 			time;
	pthread_mutex_t	alive_l;
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
char				*ft_itoa(long n);
size_t				ft_strlcat(char *dst, char *src);
long	g_ms(void);
int	getlen(long n);

#endif

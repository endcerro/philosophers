/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 18:34:51 by edal--ce          #+#    #+#             */
/*   Updated: 2021/01/10 17:35:57 by edal--ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO1_H
# define PHILO1_H

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
	struct timeval	start;
}					t_contr;
typedef	struct		s_philo
{
	int				id;
	int				alive;
	struct timeval	lmeal;
	pthread_mutex_t	alive_l;
	t_contr			*contr;
}					t_philo;
struct s_contr		*contr;
void				init_contr(t_contr *contr, char **argv, int argc);
void				print_ts(t_philo *phil, int action);
void				life(t_philo *phil);
int					eat(t_philo *phil);
int					check_alive(t_philo *phil);
int					ft_atoi(const char *in);
void				ft_putstr(char *str);
int					ft_strlen(char *str);
char				*ft_itoa(unsigned long n);
size_t				ft_strlcat(char *dst, char *src, size_t size);

#endif
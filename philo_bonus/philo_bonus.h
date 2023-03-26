/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:39:14 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/25 15:50:21 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <semaphore.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

enum e_fd
{
	in,
	out,
	err,
};

enum e_state
{
	SLEEPING,
	THINKING,
	TAKE_FORKS,
	EATING,
};

enum e_error
{
	WRG_INPUT,
	NB_INPUT,
};

typedef struct s_philos
{
	int				id;
	int				state;
	int				eat_times;
	struct timeval	start_eat;
	struct timeval	start_sleep;
}				t_philos;

typedef struct s_tab
{
	int				num_philo;
	int				meal_cnt;
	char			*forks;
	char			*post;
	pid_t			parent;
	sem_t			*sem_f;
	sem_t			*sem_p;
	t_philos		philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	struct timeval	start;
}				t_tab;

unsigned long	gap_time(struct timeval v);
int				shut_thinking(t_tab *t);
int				start_child(t_tab *t);
int				just_chillin(t_tab *t);
int				print_error(int str);
int				start_dad(t_tab *t);
int				deadly_af(t_tab *t);
int				ft_atoi(char *str);
int				lets_eat(t_tab *t);
int				wake(t_tab *t);

#endif
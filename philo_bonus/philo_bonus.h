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
	TAKE_FORKS,
	EATING,
	DEAD,
	THINKING,
	FULL,
};

enum e_error
{
	WRG_INPUT,
	NB_INPUT,
};

typedef struct s_philos
{
	int				id;
	int				eat_times;
	int				state;
	int				prev_state;
	int				full;
	// pthread_t		th;
	// struct s_tab	*tab;
	struct timeval	start_sleep;
	struct timeval	start_eat;
	// pthread_mutex_t	*fork_r;
	// pthread_mutex_t	*fork_l;
}				t_philos;

typedef struct s_tab
{
	char			*forks;
	char			*post;
	pid_t			parent;
	sem_t			*sem_f;
	sem_t			*sem_p;
	int				num_philo;
	int				meal_cnt;
	int				full;
	t_philos		philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	struct timeval	start;
	// pthread_mutex_t	*forks;
}				t_tab;

unsigned long	gap_time(struct timeval v);
// int				take_fork_act(t_philos *philo, int i);
// int				send_state(t_philos *philo, int i);
// int				final_act(t_philos *philo, int i);
// int				think_act(t_philos *philo, int i);
// int				sleep_act(t_philos *philo, int i);
// int				eat_act(t_philos *philo, int i);
int				print_error(int str);
int				ft_atoi(char *str);
int	wake(t_tab *t);
int	was_fork(t_tab *t);
int	was_thinking(t_tab *t);
int	start_child(t_tab *t);
int	was_eating(t_tab *t);
int	start_dad(t_tab *t);
int	deadly_af(t_tab *t);
// int				ft_esc(t_tab *t);
// void			*check_p(void *data);

#endif
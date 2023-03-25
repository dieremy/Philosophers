/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:27 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/24 11:35:30 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

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
	pthread_t		th;
	struct s_tab	*tab;
	struct timeval	start_sleep;
	struct timeval	start_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
}				t_philos;

typedef struct s_tab
{
	int				num_philo;
	int				meal_cnt;
	int				full;
	t_philos		*philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	struct timeval	start;
	pthread_mutex_t	*forks;
}				t_tab;

unsigned long	gap_time(struct timeval v);
int				take_fork_act(t_philos *philo, int i);
int				send_state(t_philos *philo, int i);
int				final_act(t_philos *philo, int i);
int				think_act(t_philos *philo, int i);
int				sleep_act(t_philos *philo, int i);
int				eat_act(t_philos *philo, int i);
int				print_error(int str);
int				ft_atoi(char *str);
int				ft_esc(t_tab *t);
void			*check_p(void *data);

#endif

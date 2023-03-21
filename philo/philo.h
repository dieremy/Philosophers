/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:42:27 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/16 17:13:00 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
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
    TAKE_FORKS,
    THINKING,
    SLEEPING,
    EATING,
    DEAD,
};

enum e_error
{
	WRG_INPUT,
	NB_INPUT,
};

typedef struct  s_philos
{
    int             id;
    int				eat_times;
    int				state;
	int				eating;  
	int				last_meal;
    pthread_t       th; 
    unsigned long	time_to_die;
	pthread_mutex_t	check;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	struct s_tab	*tab;
}              t_philos;

typedef struct  s_tab
{
    int				num_philo;
    int				eat_times;
    int				meal_cnt;
    int             dead;
    int             full;
	pthread_t		*tid;
	unsigned long	start;
    unsigned long	time_to_eat;
    unsigned long	time_to_sleep;
    unsigned long	time_to_die;
	pthread_mutex_t	*forks;
    pthread_mutex_t	post;
	pthread_mutex_t	check;
    t_philos		*philo;
}               t_tab;

int 	ft_atoi(char *str);
int		start_th(t_tab *t);
int		case_one(t_tab *t);
int		print_error(int str);
void	messages(int str, t_philos *philo);
void	take_forks(t_philos *philo);
void	drop_forks(t_philos *philo);
void	*over_n_over(void * data);
void	*has_eaten(void *data);
void	*check_p(void *data);
void	eat(t_philos *philo);
void	ft_esc(t_tab *t);
size_t	get_time(void);

#endif

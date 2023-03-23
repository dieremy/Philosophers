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

// enum e_state
// {
//     SLEEPING = 0,
//     TAKE_FORKS = 1,
//     EATING = 2,
//     DEAD = 4,
//     THINKING = 5,
//     FULL = 10,
// };

enum e_state
{
    SLEEPING = 0,
    TAKE_FORKS = 1,
    EATING = 2,
    DEAD = 3,
    THINKING = 4,
    FULL = 5,
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
    int				prev_state;
    pthread_t       th; 
	struct s_tab	*tab;
	struct timeval	start_sleep;
	struct timeval	start_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	// int				eating;  
	// int				last_meal;
    // unsigned long	time_to_die;
	// pthread_mutex_t	check;
}              t_philos;

typedef struct  s_tab
{
    int				num_philo;
    int				meal_cnt;
    int             full;
    t_philos		*philo;
    unsigned long	time_to_die;
    unsigned long	time_to_eat;
    unsigned long	time_to_sleep;
	struct timeval	start;
	pthread_mutex_t	*forks;
    // int             dead;
	// int				checker;
	// pthread_t		*tid;
    // int				eat_times;
    // pthread_mutex_t	post;
	// pthread_mutex_t	check;
}               t_tab;

unsigned long   gap_time(struct timeval v);
void	        *check_p(void *data);
int 	        ft_atoi(char *str);
int	            send_state(t_philos *philo, int i);
int		        print_error(int str);
int             ft_esc(t_tab *t);
// void	messages(int str, t_philos *philo);
// void	take_forks(t_philos *philo);
// void	drop_forks(t_philos *philo);
// void	*over_n_over(void * data);
// void	*has_eaten(void *data);
// void	eat(t_philos *philo);

#endif

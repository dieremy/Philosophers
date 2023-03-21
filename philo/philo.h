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

enum fd_handle
{
    in,
    out,
    err,
};

enum e_bool
{
    false,
    true,
};

typedef struct  s_philos
{
    pthread_t       th; 
    int             id;
    int				time_to_die;
    int				eat_times;
    int				state;
	int				eating;  
	int				last_meal;
	pthread_mutex_t	check;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	struct s_tab	*tab;
    // int				time_to_eat;
    // int				time_to_sleep;
    // int				num_philo;
    // struct s_philos	*next;
    // struct s_philos	*prev;
}              t_philos;

typedef struct  s_tab
{
	pthread_t		*tid;
    int				num_philo;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				eat_times;
    int				meal_cnt;
    int             dead;
    int             full;
	pthread_mutex_t	*forks;
    pthread_mutex_t	post;
	pthread_mutex_t	check;
	int				start;
    t_philos		*philo;
}               t_tab;

int 	ft_atoi(char *str);
size_t	get_time(void);

#endif
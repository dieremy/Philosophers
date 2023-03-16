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

enum e_bool
{
    false,
    true,
};

typedef struct  s_philos
{
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_times;
}              t_philos;

typedef struct  s_data
{
    int			num_philo;
    int			time_to_die;
    int			time_to_eat;
    int			time_to_sleep;
    int			eat_times;
    t_philos	*table;
}               t_data;

int ft_atoi(char *str);

#endif
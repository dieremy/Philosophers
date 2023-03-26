/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:49:10 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/24 11:35:55 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tIS SLEEPING\n", gap_time(philo[i].tab->start),
		philo[i].id);
	philo[i].prev_state = SLEEPING;
	return (0);
}

int	think_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tIS THINKING\n", gap_time(philo[i].tab->start),
		philo[i].id);
	philo[i].prev_state = THINKING;
	return (0);
}

int	take_fork_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(philo[i].tab->start),
		philo[i].id);
	philo[i].prev_state = TAKE_FORKS;
	return (0);
}

int	eat_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(philo[i].tab->start),
		philo[i].id);
	printf("%lu\t%d\tIS EATING\n", gap_time(philo[i].tab->start),
		philo[i].id);
	philo[i].prev_state = EATING;
	return (0);
}

int	final_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tDIED\n", gap_time(philo[i].tab->start),
		philo[i].id);
	return (0);
}

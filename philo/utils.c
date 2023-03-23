/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:46:28 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/16 16:56:19 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	gap_time(struct timeval v)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t.tv_sec * 1000) + (t.tv_usec / 1000))
		- ((v.tv_sec * 1000) + (v.tv_usec / 1000)));
}

int	print_error(int str)
{
	if (str == NB_INPUT)
	{
		write(err, "\e[0;31mUSAGE: ./philo number_of_philosophers ", 46);
		write(err, "time_to_die time_to_eat time_to_sleep ", 38);
		write(err, "[number_of_times_each_philosopher_must_eat]\n\e[0m", 49);
	}
	if (str == WRG_INPUT)
	{
		write(err, "\e[0;31mWRONG INPUT: Philos must make an action ", 48);
		write(err, "at least for 1ms and eat at least 1 time.\n\e[0m", 47);
	}
	exit(1);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	long int	r;
	int			i;

	r = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		print_error(WRG_INPUT);
	if (str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			print_error(WRG_INPUT);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			print_error(WRG_INPUT);
		r = r * 10 + (str[i++]) - 48;
	}
	if (r > 2147483647)
		print_error(WRG_INPUT);
	return (r);
}

int	ft_esc(t_tab *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		pthread_mutex_destroy(&t->forks[i]);
		pthread_mutex_destroy(t->philo[i].fork_l);
		pthread_mutex_destroy(t->philo[i].fork_r);
		i++;
	}
	if (t->forks)
		free(t->forks);
	if (t->philo)
		free(t->philo);
	free(t);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:41:51 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/16 17:13:22 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_esc(t_tab *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		pthread_mutex_destroy(&t->forks[i]);
		pthread_mutex_destroy(&t->philo[i].check);
		i++;
	}
	pthread_mutex_destroy(&t->post);
	pthread_mutex_destroy(&t->check);
	if (t->tid)
		free(t->tid);
	if (t->forks)
		free(t->forks);
	if (t->philo)
		free(t->philo);
	free(t);
}

void	set_table(t_tab *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		t->philo[i].tab = t;
		t->philo[i].id = i + 1;
		t->philo[i].time_to_die = t->time_to_die;
		t->philo[i].eat_times = 0;
		t->philo[i].eating = 0;
		t->philo[i].state = 0;
		pthread_mutex_init(&t->philo[i].check, NULL);
		i++;
	}
}

int	init(t_tab *t)
{
	int	i;

	t->tid = malloc(sizeof(pthread_t) * t->num_philo);
	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_philo);
	t->philo = malloc(sizeof(t_philos) * t->num_philo);
	i = -1;
	while (++i < t->num_philo)
		pthread_mutex_init(&t->forks[i], NULL);
	i = 0;
	t->philo[0].fork_l = &t->forks[0];
	t->philo[0].fork_r = &t->forks[t->num_philo - 1];
	i = 1;
	while (i < t->num_philo)
	{
		t->philo[i].fork_l = &t->forks[i];
		t->philo[i].fork_r = &t->forks[i - 1];
		i++;
	}
	set_table(t);
	return (0);
}	

int	check_params(t_tab *t, int ac, char *av[])
{
	t->num_philo = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->meal_cnt = -1;
	t->dead = 0;
	t->full = 0;
	if (ac == 6)
		t->meal_cnt = ft_atoi(av[5]);
	write(out, "TIME\tPHILO\tACTION\n\n", 19);
	pthread_mutex_init(&t->post, NULL);
	pthread_mutex_init(&t->check, NULL);
	if (init(t))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_tab		*data;
	
	if (ac < 5 || ac > 6)
		print_error(NB_INPUT);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		print_error(WRG_INPUT);
	else
	{
		data = (t_tab *)malloc(sizeof(t_tab));
		if (check_params(data, ac, av))
			return (1);
		if (start_th(data))
			return (1);
		if (data->num_philo > 1)
			ft_esc(data);
	}	
    return (0);
}

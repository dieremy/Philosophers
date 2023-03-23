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

int	send_state(t_philos *philo, int i)
{
	if (philo->tab->meal_cnt != 0
		&& philo->tab->full == philo->tab->num_philo)	
		return (0);	
	if (gap_time(philo[i].start_sleep) > philo[i].tab->time_to_die)
        philo[i].state = DEAD;
	if (philo[i].prev_state != philo[i].state)
	{
        if (philo[i].state == SLEEPING)
            sleep_act(philo, i);
        else if (philo[i].state == THINKING)
            think_act(philo, i);
        else if (philo[i].state == TAKE_FORKS)
			take_fork_act(philo, i);
        else if (philo[i].state == EATING)
			eat_act(philo, i);
        else if (philo[i].state == DEAD)
			if (!final_act(philo, i))
				return (0);
	}
	return (1);
}

void	set_table(t_philos *philo, t_tab *t)
{
	int	i;

	i = -1;
	while (++i < t->num_philo)
	{
		philo[i].fork_l = t->forks + i;
		if (i == t->num_philo - 1)
			philo[i].fork_r = t->forks;
		else
			philo[i].fork_r = (t->forks + i + 1);
	}
	i = -1;
	while (++i < t->num_philo)
		pthread_create(&philo[i].th, NULL, &check_p, philo + i);
}

int	init(t_philos *philo, t_tab *t)
{
	int	i;

	i = -1;
	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_philo);
	while (++i < t->num_philo)
	{
		philo[i].tab = t;
		philo[i].id = i;
		pthread_mutex_init(t->forks + i, NULL);
		philo[i].state = THINKING;
		philo[i].prev_state = SLEEPING;
		philo[i].eat_times = 0;
		gettimeofday(&philo[i].start_sleep, NULL);
	}
	set_table(t->philo, t);
	return (0);
}	

int	check_params(t_tab *t, int ac, char *av[])
{
	t->num_philo = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->meal_cnt = -1;
	t->full = 0;
	if (ac == 6)
		t->meal_cnt = ft_atoi(av[5]);
	if (t->time_to_die < 60 || t->time_to_sleep < 60 || t->time_to_eat < 60)
		print_error(WRG_INPUT); //control leaks here
	write(out, "TIME\tPHILO\tACTION\n\n", 19);
	gettimeofday(&t->start, NULL);
	t->philo = malloc(sizeof(t_philos) * t->num_philo);
	if (init(t->philo, t))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_tab		*data;
	int			i;
	
	if (ac < 5 || ac > 6)
		print_error(NB_INPUT);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		print_error(WRG_INPUT);
	else
	{
		data = (t_tab *)malloc(sizeof(t_tab));
		if (check_params(data, ac, av))
			return (1);
		while (1)
		{
			i = -1;
			while (++i < data->num_philo)
				if (!send_state(data->philo, i))
					return (0);
		}
		ft_esc(data);
	}	
    return (0);
}

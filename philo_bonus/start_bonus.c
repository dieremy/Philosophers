/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:43:19 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/25 17:05:48 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	wake(t_tab *t)
{
	deadly_af(t);
	if (gap_time(t->philo.start_sleep) >= t->time_to_sleep)
	{
		t->philo.state = THINKING;
		was_thinking(t);
		return (0);
	}
	return (1);
}

int	was_thinking(t_tab *t)
{
	sem_wait(t->sem_p);
	printf("%lu\t%d\tIS THINKING\n", gap_time(t->start), t->philo.id);
	sem_post(t->sem_p);
	deadly_af(t);
	sem_wait(t->sem_f);
	sem_wait(t->sem_p);
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(t->start), t->philo.id);
	sem_post(t->sem_p);
	deadly_af(t);
	t->philo.state = TAKE_FORKS;
	was_fork(t);
	return (0);
}

int	was_fork(t_tab *t)
{
	if (t->num_philo == 1)
	{
		sem_wait(t->sem_p);
		printf("%lu\t%d\tDIED\n", gap_time(t->start), t->philo.id);
		exit(0);
	}
	deadly_af(t);
	sem_wait(t->sem_f);
	sem_wait(t->sem_p);
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(t->start), t->philo.id);
	printf("%lu\t%d\tIS EATING\n", gap_time(t->start), t->philo.id);
	sem_post(t->sem_p);
	deadly_af(t);
	gettimeofday(&t->philo.start_eat, NULL);
	t->philo.state = EATING;
	was_eating(t);
	return (0);
}

int	was_eating(t_tab *t)
{
	deadly_af(t);
	if (gap_time(t->philo.start_eat) >= t->time_to_eat)
	{
		t->philo.eat_times++;
		if (t->philo.eat_times == t->meal_cnt)
		{
			sem_post(t->sem_f);
			sem_post(t->sem_f);
			sem_unlink("/post");
			sem_unlink("/forks");
			sem_close(t->sem_f);
			sem_close(t->sem_p);
			exit(1);
		}
		sem_post(t->sem_f);
		sem_post(t->sem_f);
		sem_wait(t->sem_p);
		printf("%lu\t%d\tIS SLEEPING\n", gap_time(t->start), t->philo.id);
		sem_post(t->sem_p);
		gettimeofday(&t->philo.start_sleep, NULL);
		t->philo.state = SLEEPING;
		wake(t);
		return (0);
	}	
	return (1);
}

int	start_child(t_tab *t)
{
	t->philo.state = THINKING;
	gettimeofday(&t->philo.start_sleep, NULL);
	gettimeofday(&t->start, NULL);
	while (1)
	{
		if (t->philo.state == SLEEPING)
			wake(t);
		if (t->philo.state == THINKING)
			was_thinking(t);
		else if (t->philo.state == TAKE_FORKS)
			was_fork(t);
		else if (t->philo.state == EATING)
			was_eating(t);
	}
	return (0);
}

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

void	init(t_tab *t)
{
	int	i;

	i = 0;
	t->philo = malloc(sizeof(t_philos) * t->num_philo);
	while (i < t->num_philo)
	{
		t->philo[i].id = i + 1;
		t->philo[i].tab = t;
		if (i + 1 == t->num_philo)
			t->philo[i].next = &t->philo[0];
		else
			t->philo[i].next = &t->philo[i + 1];
		if (i == 0)
			t->philo[i].prev = &t->philo[t->num_philo - 1];
		else
			t->philo[i].prev = &t->philo[i - 1];
		pthread_mutex_init(&t->philo[i].fork, NULL);
		i++;
	}
	// pthreads_mutex_init(&t->post, NULL);
	// pthreads_mutex_init(&t->post, NULL);
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
	init(t);
	return (0);
}

void	*cicle(void *data)
{
	t_philos	*philo;
	t_tab		*t;

	philo = (t_philos *)data;
	t = philo->tab;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!t->dead && !t->full)
	{
		// eat();
		// mess()
		// during();
		// mess();
	}
	return (NULL);
}

void	run(t_tab *t, pthread_t *th)
{
	int	i;

	pthread_mutex_init(&t->post, NULL);
	pthread_mutex_init(&t->post, NULL);
	i = 0;
	while (i < t->num_philo)
	{
		if (pthread_create(&th[i], NULL, &cicle, &t->philo[i]))
		{
			free(t->philo);
			free(th);
		}
		pthread_mutex_lock(&t->post);
		t->philo[i].last_meal = t->start;
		pthread_mutex_unlock(&t->post);
		i++;
	}

}

int	main(int ac, char **av)
{
	t_tab		*params;
	pthread_t	*th;
	
	if (ac < 5 || ac > 6 || ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
	{
		write(err, "usage: ./philo [number_of_philosophers] ", 40);
		write(err, "[time_to_die] [time_to_eat] [time_to_sleep]\n", 44);
		return (1);
	}
	else
	{
		params = (t_tab *)malloc(sizeof(t_tab));
		if (!params)
			return (-1);
		check_params(params, ac, av);
		// pthreads_mutex_init(&params->post, NULL);
		// pthreads_mutex_init(&params->post, NULL);
		th = (pthread_t *)malloc(sizeof(pthread_t) * params->num_philo);
		params->start = get_time();
		run(params, th);
		// printf("philo num %d\n", params->num_philo);
		// printf("TTD %d\n", params->time_to_die);
		// printf("TTE %d\n", params->time_to_eat);
		// printf("TTS %d\n", params->time_to_sleep);
		// if (ac == 6)
		// 	printf("meal cnt %d\n", params->meal_cnt);
		free(params);
	}	
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robegarc <robegarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:34:24 by robegarc          #+#    #+#             */
/*   Updated: 2023/03/25 16:51:19 by robegarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_dad(t_tab *t)
{
	int	cnt_m;
	int	state;

	cnt_m = 0;
	while (waitpid(0, &state, 0))
	{
		if (((state >> 8) & 0x0000000ff) == 0)
		{
			kill(0, SIGKILL);
			break;
		}
		if (((state >> 8) & 0x0000000ff) == 1)
		{
			cnt_m++;
			if (cnt_m == t->num_philo)
				break;
		}
	}
	return (0);

	// int	count_m;
	// int	status;

	// count_m = 0;
	// while (waitpid(0, &status, 0))
	// {
	// 	if (((status >> 8) & 0x0000000ff) == 0)
	// 	{
	// 		kill(0, SIGKILL);
	// 		break ;
	// 	}
	// 	if (((status >> 8) & 0x0000000ff) == 1)
	// 	{
	// 		count_m++;
	// 		if (count_m == t->num_philo)
	// 			break ;
	// 	}
	// }
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
		print_error(WRG_INPUT);
	write(out, "TIME\tPHILO\tACTION\n\n", 19);
	t->forks = "/forks";
	t->post = "/post";
	sem_unlink(t->forks);
	sem_unlink(t->post);
	t->sem_f = sem_open(t->forks, O_CREAT, 0666, t->num_philo);
	t->sem_p = sem_open(t->post, O_CREAT, 0666, 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_tab		*t;
	int			i;

	if (ac < 5 || ac > 6)
		print_error(NB_INPUT);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		print_error(WRG_INPUT);
	else
	{
		t = (t_tab *)malloc(sizeof(t_tab));
		if (check_params(t, ac, av))
			return (1);
		i = 0;
		while (i < t->num_philo)
		{
			t->parent = fork();
			if (!t->parent)
			{
				t->philo.id = i + 1;
				break;
			}
			i++;
		}
		if (!t->parent)
			start_child(t);
		start_dad(t);
		// sem_close(t->sem_f);
		// sem_close(t->sem_p);
		free(t);
	}	
	return (0);
}
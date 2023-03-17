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

void	init(t_tab *tab)
{
	t_philos	*philos;
	int			i;

	tab->forks = malloc(sizeof(pthreads_mutex_t) * tab->num_philo);
	
	i = 0;

}

int	check_params(t_tab *tab, int ac, char *av[])
{
	tab->num_philo = ft_atoi(av[1]);
	tab->time_to_die = ft_atoi(av[2]);
	tab->time_to_eat = ft_atoi(av[3]);
	tab->time_to_sleep = ft_atoi(av[4]);
	tab->meal_cnt = -1;
	if (ac == 6)
		tab->meal_cnt = ft_atoi(av[5]);
	init(tab);
	return (1);
}

int	main(int ac, char **av)
{
	t_tab	*params;
	
	if (ac < 5 || ac > 6)
	{
		printf("usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
		return (1);
	}
	else
	{
		params = (t_tab *)malloc(sizeof(t_tab));
		if (!params)
			return (1);
		check_params(params, ac, av);
		printf("philo num %d\n", params->num_philo);
		printf("TTD %d\n", params->time_to_die);
		printf("TTE %d\n", params->time_to_eat);
		printf("TTS %d\n", params->time_to_sleep);
		if (ac == 6)
			printf("meal cnt %d\n", params->meal_cnt);
		free(params);
	}	
    return (0);
}
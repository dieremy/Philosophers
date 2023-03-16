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

void	init_params(t_data *init, char *av[])
{
	init->num_philo = ft_atoi(av[1]);
	init->time_to_die = ft_atoi(av[2]);
	init->time_to_eat = ft_atoi(av[3]);
	init->time_to_sleep = ft_atoi(av[4]);
}

int	main(int ac, char **av)
{
	t_data	*params;
	
	if (ac != 6)
		printf("usage: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]\n");
	else
	{
		params = (t_data *)malloc(sizeof(t_data));
		if (!params)
			return (1);
		init_params(params, av);
		printf("philo num %d\n", params->num_philo);
		printf("TTD %d\n", params->time_to_die);
		printf("TTE %d\n", params->time_to_eat);
		printf("TTS %d\n", params->time_to_sleep);
		free(params);
	}	
    return (0);
}
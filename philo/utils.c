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

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	print_error()
{
	write(err, "Error\n", 6);
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
	if (str[i] == '+')
	{
		if (!ft_isdigit(str[i + 1]))
			print_error();
		i++;
	}
	if (str[i] == '-')
		print_error();
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			print_error();
		r = r * 10 + (str[i++]) - 48;
	}
	if (r > 2147483647)
		print_error();
	return (r);
}
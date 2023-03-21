#include "philo.h"

int	case_one(t_tab *t)
{
	pthread_create(&t->tid[0], NULL, &over_n_over, &t->philo[0]);
	pthread_detach(t->tid[0]);
	while (t->dead == 0)
		usleep(0);
	ft_esc(t);
	return (0);
}

void	*check_p(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	pthread_mutex_lock(&philo->tab->post);
	// printf("data val: %d\n", philo->tab->dead);
	pthread_mutex_unlock(&philo->tab->post);
	while (philo->tab->dead == 0)
	{
		pthread_mutex_unlock(&philo->check);
		if (philo->tab->full >= philo->tab->num_philo)
			philo->tab->dead = 1;
		pthread_mutex_unlock(&philo->check);
	}
	return (0);
}

void	*has_eaten(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	while (philo->tab->dead == 0)
	{
		pthread_mutex_lock(&philo->check);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			messages(DEAD, philo);
		if (philo->eat_times == philo->tab->meal_cnt)
		{
			pthread_mutex_lock(&philo->tab->check);
			philo->tab->full++;
			philo->eat_times++;
			pthread_mutex_unlock(&philo->tab->check);
		}
		pthread_mutex_unlock(&philo->check);
	}
	return (0);
}

void	*over_n_over(void * data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	philo->time_to_die = philo->tab->time_to_die + get_time();
	pthread_create(&philo->th, NULL, &has_eaten, (void *)philo);
	while (philo->tab->dead == 0)
	{
		eat(philo);
		messages(THINKING, philo);
	}
	pthread_join(philo->th, NULL);
	return (0);
}


int	start_th(t_tab *t)
{
	pthread_t	th0;
	int			i;

	i = -1;
	t->start = get_time();
	if (t->num_philo == 1)
			return (case_one(t));
	if (t->meal_cnt > 0)
		pthread_create(&th0, NULL, &check_p, &t->philo[0]);
	while (++i < t->num_philo)
	{
		pthread_create(&t->tid[i], NULL, &over_n_over, &t->philo[i]);
		usleep(1);
	}
	i = -1;
	while (++i < t->num_philo)
		pthread_join(t->tid[i], NULL);
	return (0);
}
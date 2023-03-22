#include "philo.h"

// int	case_one(t_tab *t)
// {
// 	pthread_create(&t->tid[0], NULL, &over_n_over, &t->philo[0]);
// 	pthread_detach(t->tid[0]);
// 	while (t->dead == 0)
// 		usleep(0);
// 	ft_esc(t);
// 	return (0);
// }

void	sleeping(t_philos *philo)
{
	if (get_time(philo->start_sleep) >= philo->tab->time_to_sleep)
	{
		philo->prev_state = SLEEPING;
		philo->state = THINKING;
		return ;
	}
}

void	thinking(t_philos *philo)
{
	if (pthread_mutex_lock(philo->fork_l) == 0)
		philo->state = TAKE_FORKS;
}

void	take_forks(t_philos *philo)
{
	if (philo->tab->num_philo == 1)
		philo->state = DEAD;
	else if (pthread_mutex_lock(philo->fork_r) == 0)
	{
		philo->state = EATING;
		gettimeofday(&philo->start_eat, NULL);
		return ;
	}
}

void	eating(t_philos *philo)
{
	if (get_time(philo->start_eat) >= philo->tab->time_to_eat)
	{
		philo->state = THINKING;
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (philo->tab->meal_cnt > 0)
		{
			philo->eat_times++;
			if (philo->eat_times == philo->tab->meal_cnt)
			{
				philo->state = 10;
				philo->tab->full++;
				return ;
			}
		}
		gettimeofday(&philo->start_sleep, NULL);
		return ;
	}
}

void	*check_p(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	// pthread_mutex_lock(&philo->tab->post);
	// printf("data val: %d\n", philo->tab->dead);
	// pthread_mutex_unlock(&philo->tab->post);
	while (!philo->tab->checker)
		continue ;
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		// pthread_mutex_unlock(&philo->check);
		// if (philo->tab->full >= philo->tab->num_philo)
		// 	philo->tab->dead = 1;
		// pthread_mutex_unlock(&philo->check);
	}
	while (1)
	{
		usleep(100);
		if (philo->state == SLEEPING)
			sleeping(philo);
		else if (philo->state == THINKING)
			thinking(philo);
		else if (philo->state == TAKE_FORKS)
			take_forks(philo);
		else if (philo->state == EATING)
			eating(philo);
		else if (philo->state == 10)
			gettimeofday(&philo->start_sleep, NULL);
	}
	return (0);
}

// void	*has_eaten(void *data)
// {
// 	t_philos	*philo;

// 	philo = (t_philos *)data;
// 	while (philo->tab->dead == 0)
// 	{
// 		pthread_mutex_lock(&philo->check);
// 		if (get_time() >= philo->time_to_die && philo->eating == 0)
// 			messages(DEAD, philo);
// 		if (philo->eat_times == philo->tab->meal_cnt)
// 		{
// 			pthread_mutex_lock(&philo->tab->check);
// 			philo->tab->full++;
// 			philo->eat_times++;
// 			pthread_mutex_unlock(&philo->tab->check);
// 		}
// 		pthread_mutex_unlock(&philo->check);
// 	}
// 	return (0);
// }

// void	*over_n_over(void * data)
// {
// 	t_philos	*philo;

// 	philo = (t_philos *)data;
// 	philo->time_to_die = philo->tab->time_to_die + get_time();
// 	pthread_create(&philo->th, NULL, &has_eaten, (void *)philo);
// 	while (philo->tab->dead == 0)
// 	{
// 		eat(philo);
// 		messages(THINKING, philo);
// 	}
// 	pthread_join(philo->th, NULL);
// 	return (0);
// }


int	print_state(t_philos *philo, int i)
{
	if (philo->tab->meal_cnt != 0
		&& philo->tab->full == philo->tab->num_philo)	
		return (0);	
	if (get_time(philo[i].start_sleep) > philo[i].tab->time_to_die)
		philo[i].state = DEAD;
	if (philo[i].prev_state != philo[i].state)
	{
		if (philo[i].state == SLEEPING)
		{
			printf("%lu\t%d\tIS SLEEPING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = SLEEPING;
		}
		if (philo[i].state == THINKING)
		{
			printf("%lu\t%d\tIS THINKING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = THINKING;
		}
		if (philo[i].state == TAKE_FORKS)
		{
			printf("%lu\t%d\tHAS TAKEN A FORK\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = TAKE_FORKS;
		}
		if (philo[i].state == EATING)
		{
			printf("%lu\t%d\tHAS TAKEN A FORK\n", get_time(philo[i].tab->start),
				philo[i].id);
			printf("%lu\t%d\tIS EATING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = EATING;
		}
		if (philo[i].state == DEAD)
		{
			printf("%lu\t%d\tDEAD AF\n", get_time(philo[i].tab->start),
				philo[i].id);
			return (0);
		}
	}
	return (1);
}
// 	if (t->num_philo == 1)
// 			return (case_one(t));
// 	if (t->meal_cnt > 0)
// 		pthread_create(&th0, NULL, &check_p, &t->philo[0]);
// 	while (++i < t->num_philo)
// 	{
// 		pthread_create(&t->tid[i], NULL, &over_n_over, &t->philo[i]);
// 		usleep(1);
// 	}
// 	i = -1;
// 	while (++i < t->num_philo)
// 		pthread_join(t->tid[i], NULL);
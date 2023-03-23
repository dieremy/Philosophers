#include "philo.h"

int	wake(t_philos *philo)
{//status zero
	if (gap_time(philo->start_sleep) >= philo->tab->time_to_sleep)
	{
		philo->prev_state = SLEEPING;
		philo->state = THINKING;
		return (0);
	}
	return (1);
}

int	take_fork(t_philos *philo)
{//state 1
	if (pthread_mutex_lock(philo->fork_l) == 0)
		philo->state = TAKE_FORKS;
	return (0);
}

int	start_eating(t_philos *philo)
{
	if (philo->tab->num_philo == 1)
		philo->state = DEAD;
	else if (pthread_mutex_lock(philo->fork_r) == 0)
	{
		philo->state = EATING;
		gettimeofday(&philo->start_eat, NULL);
		return (0);
	}
	return (0);
}

int	shut_your_mouth(t_philos *philo)
{ //status three
	if (gap_time(philo->start_eat) >= philo->tab->time_to_eat)
	{
		philo->state = SLEEPING;
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (philo->tab->meal_cnt > 0)
		{
			philo->eat_times++;
			if (philo->eat_times == philo->tab->meal_cnt)
			{
				philo->state = FULL;
				philo->tab->full++;
				return (0);
			}
		}
		gettimeofday(&philo->start_sleep, NULL);
		return (0);
	}
	return (1);
}

void	*check_p(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		usleep(100);
		if (philo->state == SLEEPING)
			wake(philo); //status zero
		else if (philo->state == THINKING)
			take_fork(philo); //status 1
		else if (philo->state == TAKE_FORKS)
			start_eating(philo); //status two
		else if (philo->state == EATING)
			shut_your_mouth(philo); //status 3
		else if (philo->state == FULL)
			gettimeofday(&philo->start_sleep, NULL);
	}
	return (0);
}

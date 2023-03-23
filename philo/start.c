#include "philo.h"

void	sleeping(t_philos *philo)
{//status zero
	if (get_time(philo->start_sleep) >= philo->tab->time_to_sleep)
	{
		philo->prev_state = 0; //0 //sleeping
		philo->state = 5; //5 //thinking
		return ;
	}
}

void	thinking(t_philos *philo)
{//state 1
	if (pthread_mutex_lock(philo->fork_l) == 0)
		philo->state = 1; //1 //take forks
}

void	take_forks(t_philos *philo)
{ //status two
	if (philo->tab->num_philo == 1)
		philo->state = 4; //4 //dead
	else if (pthread_mutex_lock(philo->fork_r) == 0)
	{
		philo->state = 2; //2 eating
		gettimeofday(&philo->start_eat, NULL);
		return ;
	}
}

void	eating(t_philos *philo)
{ //status three
	if (get_time(philo->start_eat) >= philo->tab->time_to_eat)
	{
		philo->state = 0; //0 thinking
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
	while (!philo->tab->checker)
		continue ;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		usleep(100);
		if (philo->state == 0) //0 //sleeping
			sleeping(philo); //status zero
		else if (philo->state == 5) //5 //thinking
			thinking(philo); //status 1
		else if (philo->state == 1) //1 take fork
			take_forks(philo); //status two
		else if (philo->state == 2) //2 //eating
			eating(philo); //status 3
		else if (philo->state == 10)
			gettimeofday(&philo->start_sleep, NULL);
	}
	return (0);
}

int	print_state(t_philos *philo, int i)
{
	if (philo->tab->meal_cnt != 0
		&& philo->tab->full == philo->tab->num_philo)	
		return (0);	
	if (get_time(philo[i].start_sleep) > philo[i].tab->time_to_die)
		philo[i].state = 4; //4 //dead
	if (philo[i].prev_state != philo[i].state)
	{
		if (philo[i].state == 0) //0 sleeping
		{//status zero
			printf("%lu\t%d\tIS SLEEPING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = 0; //0 sleeping
		}
		else if (philo[i].state == 5) //5 thinking
		{//status five
			printf("%lu\t%d\tIS THINKING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = 5; //5 thinking
		}
		else if (philo[i].state == 1) //1 take forks
		{//status one
			printf("%lu\t%d\tHAS TAKEN A FORK\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = 1; //1 take forks
		}
		else if (philo[i].state == 2) //2 eating
		{//status two
			printf("%lu\t%d\tHAS TAKEN A FORK\n", get_time(philo[i].tab->start),
				philo[i].id);
			printf("%lu\t%d\tIS EATING\n", get_time(philo[i].tab->start),
				philo[i].id);
			philo[i].prev_state = 2; //2 eating
		}
		else if (philo[i].state == 4) //4 dead
		{
			printf("%lu\t%d\tDEAD AF\n", get_time(philo[i].tab->start),
				philo[i].id);
			return (0);
		}
	}
	return (1);
}

#include "philo.h"

int    sleep_act(t_philos *philo, int i)
{
    printf("%lu\t%d\tIS SLEEPING\n", gap_time(philo[i].tab->start),
        philo[i].id);
    philo[i].prev_state = SLEEPING;
	return (0);
}

int think_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tIS THINKING\n", gap_time(philo[i].tab->start),
        philo[i].id);
    philo[i].prev_state = THINKING;
	return (0);
}

int take_fork_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(philo[i].tab->start),
		philo[i].id);
    philo[i].prev_state = TAKE_FORKS;
	return (0);
}

int eat_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(philo[i].tab->start),
		philo[i].id);
	printf("%lu\t%d\tIS EATING\n", gap_time(philo[i].tab->start),
		philo[i].id);
    philo[i].prev_state = EATING;
	return (0);
}

int	final_act(t_philos *philo, int i)
{
	printf("%lu\t%d\tDEAD AF\n", gap_time(philo[i].tab->start),
		philo[i].id);
	return (0);
}

// int	send_state(t_philos *philo, int i)
// {
// 	if (philo->tab->meal_cnt != 0
// 		&& philo->tab->full == philo->tab->num_philo)	
// 		return (0);	
// 	if (gap_time(philo[i].start_sleep) > philo[i].tab->time_to_die)
//         philo[i].state = DEAD;
// 	if (philo[i].prev_state != philo[i].state)
// 	{
//         if (philo[i].state == SLEEPING)
//             sleep_act(philo, i);
//         else if (philo[i].state == THINKING)
//             think_act(philo, i);
//         else if (philo[i].state == TAKE_FORKS)
// 			take_fork_act(philo, i);
//         else if (philo[i].state == EATING)
// 			eat_act(philo, i);
//         else if (philo[i].state == DEAD)
// 		{
// 			printf("%lu\t%d\tDEAD AF\n", gap_time(philo[i].tab->start),
// 				philo[i].id);
// 			return (0);
// // 			if (!final_act(philo, i))
// 		}
// 	}
// 	return (1);
// }

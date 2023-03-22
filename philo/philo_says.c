// #include "philo.h"

// void	messages(int str, t_philos *philo)
// {
// 	long long unsigned	time;

// 	pthread_mutex_lock(&philo->tab->post);
// 	time = get_time() - philo->tab->start;
// 	if (str == DEAD && philo->tab->dead == 0)
// 	{
// 		printf("%llu\t%d\tDEAD AF\n", time, philo->id);
// 		philo->tab->dead = 1;
// 	}
// 	if (philo->tab->dead == 0)
// 	{
// 		if (str == TAKE_FORKS)
// 			printf("%llu\t%d\tHAS TAKEN A FORK\n", time, philo->id);
// 		if (str == EATING)
// 			printf("%llu\t%d\tIS EATING\n", time, philo->id);
// 		if (str == SLEEPING)
// 			printf("%llu\t%d\tIS SLEEPING\n", time, philo->id);
// 		if (str == THINKING)
// 			printf("%llu\t%d\tIS THINKING\n", time, philo->id);
// 	}
// 	pthread_mutex_unlock(&philo->tab->post);
// }

// // void	take_forks(t_philos *philo)
// // {
// // 	pthread_mutex_lock(philo->fork_r);
// // 	messages(TAKE_FORKS, philo);
// // 	pthread_mutex_lock(philo->fork_l);
// // 	messages(TAKE_FORKS, philo);
// // }

// void	drop_forks(t_philos *philo)
// {
// 	pthread_mutex_unlock(philo->fork_l);
// 	pthread_mutex_unlock(philo->fork_r);
// 	messages(SLEEPING, philo);
// 	usleep(philo->tab->time_to_sleep);
// }

// void	eat(t_philos *philo)
// {
// 	take_forks(philo);
// 	pthread_mutex_lock(&philo->check);
// 	philo->eating = 1;
// 	philo->time_to_die = get_time() + philo->tab->time_to_die;
// 	messages(EATING, philo);
// 	philo->eat_times++;
// 	usleep(philo->tab->time_to_eat);
// 	philo->eating = 0;
// 	pthread_mutex_unlock(&philo->check);
// 	drop_forks(philo);
// }
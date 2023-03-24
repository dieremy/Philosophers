#include "philo_b.h"

int	state_zero(t_tab *t)
{
	check_death(t);
	if (gap_time(t->philo.start_sleep) >= t->time_to_sleep)
	{
		t->philo.state = 1;
		state_one(t);
	}
	return (0);
}

int	state_one(t_tab *t)
{
	sem_wait(t->post); //lock
	printf("%lu\t%d\tIS THINKING\n", gap_time(t->start), t->philo.id);
	sem_post(t->post); //unlock
	check_death(t);
	sem_wait(t->sem);
	sem_wait(t->post);
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(t->start), t->philo.id);
	sem_post(t->post);
	check_death(t);
	t->philo.state = 2;
	state_two(t);
	return (0);
}

int	state_two(t_tab *t)
{
	if (t->num_philo == 1)
	{
		sem_wait(t->post);
		printf("%lu\t%d\tDIED\n", gap_time(t->start), t->philo.id);
		if (t->philo.state == 3)
			sem_post(t->sem); //unlock
		sem_post(t->sem);
		exit (0);
	}
	check_death(t);
	sem_wait(t->sem); //lock
	sem_wait(t->post);
	printf("%lu\t%d\tHAS TAKEN A FORK\n", gap_time(t->start), t->philo.id);
	printf("%lu\t%d\tIS EATING\n", gap_time(t->start), t->philo.id);
	sem_post(t->post);
	check_death(t);
	gettimeofday(&t->philo.start_eat, NULL);
	t->philo.state = 3;
	state_three(t);
	return (0);
}

int	state_three(t_tab *t)
{
	check_death(t);
	if (gap_time(t->philo.start_eat) >= t->time_to_eat)
	{
		t->philo.eat_times++;
		if (t->philo.eat_times == t->meal_cnt)
		{
			sem_post(t->sem); //unlock
			sem_post(t->sem);
			sem_unlink("/forks");
			sem_unlink("/post");
			sem_close(t->sem);
			sem_close(t->post);
			exit (1);
		}
		sem_post(t->sem);
		sem_post(t->sem);
		sem_wait(t->post); //lock
		printf("%lu\t%d\tIS SLEEPING\n", gap_time(t->start), t->philo.id);
		sem_post(t->post);
		gettimeofday(&t->philo.start_sleep, NULL);
		t->philo.state = 0;
		state_zero(t);
	}
	return (0);
}

int	start_child(t_tab *t)
{
	t->philo.eat_times = 0;
	t->philo.state = 1;
	gettimeofday(&t->philo.start_sleep, NULL);
	gettimeofday(&t->start, NULL);
	while (1)
	{
		if (t->philo.state == 0)
			state_zero(t);
		else if (t->philo.state == 1)
			state_one(t);
		else if (t->philo.state == 3)
			state_three(t);
	}
	return (0);
}
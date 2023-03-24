#include "philo_b.h"

int	start_parent(t_tab *t)
{
	int	cnt_m;
	int	state;

	cnt_m = 0;
	while (waitpid(0, &state, 0))
	{
		if (((state >> 8) & 0x0000000ff) == 0)
		{
			kill(0, SIGKILL);
			break;
		}
		if (((state >> 8) & 0x0000000ff) == 1)
		{
			cnt_m++;
			if (cnt_m == t->num_philo)
				break;
		}
	}
	return (0);
}

int	check_params(t_tab *t, int ac, char **av)
{
	char	*forks;
	char	*post;

	t->num_philo = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->meal_cnt = -1;
	// t->philo.eat_times = 0;
	if (ac == 6)
		t->meal_cnt = ft_atoi(av[5]);
	if (t->time_to_die < 60 || t->time_to_sleep < 60 || t->time_to_eat < 60)
		print_error(WRG_INPUT);
	forks = "/forks";
	post = "/post";
	sem_unlink(forks);
	sem_unlink(post);
	t->sem = sem_open(forks, O_CREAT, 0666, t->num_philo);
	t->post = sem_open(post, O_CREAT, 0666, 1);
	return (0);
}

int main(int ac, char **av)
{
    t_tab   *t;
    int     i;

    if (ac < 5 || ac > 6)
        print_error(NB_INPUT);
    if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
        print_error(WRG_INPUT);
    else
    {
        t = (t_tab *)malloc(sizeof(t_tab));
		check_params(t, ac, av);
		i = -1;
		while (++i < t->num_philo)
		{
			t->parent = fork();
			if (!t->parent)
			{//if is child process
				t->philo.id = i + 1;
				break;
			}
		}
		if (!t->parent)
			start_child(t);
		start_parent(t);
    }
	// CONTROL LEAKS
    return (0);
}
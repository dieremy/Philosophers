#ifndef PHILO_B
# define PHILO_B

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

enum e_fd
{
    in,
    out,
    err,
};

enum e_state
{
    SLEEPING,
    TAKE_FORKS,
    EATING,
    DEAD,
    THINKING,
    FULL,
};

enum e_error
{
    WRG_INPUT,
    NB_INPUT,
};

typedef struct s_philos
{
    int				id;
	int				state;
    int				eat_times;
	struct timeval	start_eat;
	struct timeval	start_sleep;
}				t_philos;

typedef struct s_tab
{
	sem_t			*sem;
	sem_t			*post;
	pid_t			parent;
	int				meal_cnt;
	int				num_philo;
	t_philos		philo;
	struct timeval	start;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;

}				t_tab;

unsigned long	gap_time(struct timeval v);
int				print_error(int str);
int				ft_atoi(char *s);
int				state_zero(t_tab *t);
int				state_one(t_tab *t);
int				state_two(t_tab *t);
int				state_three(t_tab *t);
int				start_child(t_tab *t);
int				start_parent(t_tab *t);
void			check_death(t_tab *t);

#endif
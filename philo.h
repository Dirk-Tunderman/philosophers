
#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
#include <limits.h>

#define THREADS 2

#include <sys/time.h>

typedef struct thread_args one_philo;
typedef struct t_data gen_data;
typedef struct philo_node philo_node;

typedef struct t_data {
    int             num_philosophers;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             num_times_must_eat;
    long long       beginning_time;
    int             p_finish;
    int             die;
    philo_node      *philo_head;
    pthread_mutex_t *fork; // recources
    pthread_mutex_t lock; // mutex
} gen_data;

typedef struct thread_args {  // 1 or 0
    pthread_t   thread_id;
    pthread_t   death_thread_id;
    int         philosopher_id;
    int         meals_finished;
    long long   time_last_meal;
    int         l_fork;
    int         r_fork;
    gen_data    *data;
} one_philo;

typedef struct philo_node {
    one_philo philo;
    struct philo_node *next;
} philo_node;



int init_data(char *argv[], gen_data *data);
int	init_forks(gen_data *data);
int can_eat(one_philo *philo);
int	init_other_thing(gen_data *data);
void start_philosopher_threads(gen_data *data);
void *philosopher_action(void *args);
int init_mutexes(gen_data *data);
int check_philo_eaten(gen_data *data);


void think(one_philo *philo);
//void pick_up_forks(one_philo *philo);
void eat(one_philo *philo);
//void put_down_forks(one_philo *philo);
void sleep_philo(one_philo *philo);
long long get_current_time_ms();
void *check_philosopher_death(void *args);

void german_usleep(long long sleep_time);
long long time_diff(long long start, long long end);
long long timing();

long long long_atoi(const char *str);

#endif 

/*
    test 1: 1 800 200 200 the philosopher should not eat and die -> sometimes works
    test 2: 5 800 200 200 no one should die -> works
    test 3: 4 410 200 200 no one should die -> works
    test 4: 4 310 200 100 a philosopher should die -> does not work
*/
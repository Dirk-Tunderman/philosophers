
#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>

#define THREADS 2

#include <sys/time.h>

typedef struct thread_args {  // 1 or 0
    pthread_t   thread_id;
    int         philosopher_id;
    int         meals_finished;
    long long   time_last_meal;
    int         l_fork;
    int         r_fork;
    gen_data    *data;
} one_philo;

typedef struct t_data {
    int             num_philosophers;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             num_times_must_eat;
    one_philo       *philo;
    pthread_mutex_t *fork; // recources
    pthread_mutex_t lock; // mutex
} gen_data;




void init_data(char *argv[], gen_data *data);
int	init_forks(gen_data *data);


#endif 
#include "philo.h"

void init_data(char *argv[], gen_data *data)
{
    //put args in struct
    int i = 0;

    data->num_philosophers = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		data->num_times_must_eat = atoi(argv[5]);
	else
		data->num_times_must_eat = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (data->fork == NULL)
		return;
	data->philo = malloc(sizeof(one_philo) * data->num_philosophers);
	if (data->philo == NULL)
		return;
	while (i < data->num_philosophers)
	{
    	pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}


	pthread_mutex_init(&data->lock, NULL);


    //printf("num-philos: %d\n timetodie: %d\n time-to-eat: %d\n timetosleep: %d\n\n", (*data)->num_philosophers, (*data)->time_to_die, (*data)->time_to_eat, (*data)->time_to_sleep);
    //data->philosopher_states = malloc(data->num_philosophers * sizeof(int));

}

void	init_other_thing(gen_data *data)
{
	int i = 0;

	while (i < data->num_philosophers)
	{
		data->philo[i].meals_finished = 0;
		data->philo[i].time_last_meal = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philosophers;
		i++;
	}

}
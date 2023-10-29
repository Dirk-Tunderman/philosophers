#include "philo.h"

long long long_atoi(const char *str) {
    int sign = 1;
    long long res = 0;

    // Check for optional sign, and update pointer and sign accordingly
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    // Process each digit in the string
    while (*str) {
        // Check if the character is a digit
        if (*str < '0' || *str > '9') {
            break;
        }

        // Check for overflow
        if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10 && *str - '0' > LLONG_MAX % 10)) {
            if (sign == 1) {
                return LLONG_MAX;
            } else {
                return LLONG_MIN;
            }
        }

        // Update result
        res = res * 10 + (*str - '0');
        str++;
    }

    // Apply the sign to the result
    res *= sign;

    return res;
}


int init_data(char *argv[], gen_data *data)
{
    // Put args in struct
    data->num_philosophers = long_atoi(argv[1]);
    data->time_to_die = long_atoi(argv[2]);
    data->time_to_eat = long_atoi(argv[3]);
    data->time_to_sleep = long_atoi(argv[4]);

    data->done           = 0;
    data->p_finish = 0;
    if (argv[5])
        data->num_times_must_eat = atoi(argv[5]);
    else
        data->num_times_must_eat = -1;
    
    data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    if (!data->fork)
        return -1;
    if (init_mutexes(data) == -1 || init_other_thing(data) == -1)
        return -1;
    
    // printf("num-philos: %d\n timetodie: %d\n time-to-eat: %d\n timetosleep: %d\n\n", (*data)->num_philosophers, (*data)->time_to_die, (*data)->time_to_eat, (*data)->time_to_sleep);
    // data->philosopher_states = malloc(data->num_philosophers * sizeof(int));
    return 0;
}

int	init_other_thing(gen_data *data)
{
    int i = 0;
    philo_node *current_node = NULL;
    philo_node *previous_node = NULL;

    while (i < data->num_philosophers)
    {
        current_node = (philo_node *) malloc(sizeof(philo_node));
        if (current_node == NULL)
        {
            // handle memory allocation failure
            return -1;
        }

        current_node->philo.philosopher_id = i + 1;
        current_node->philo.meals_finished = 0;
        current_node->philo.time_last_meal = 0;
        current_node->philo.l_fork = i;
        current_node->philo.r_fork = (i + 1) % data->num_philosophers;
        current_node->philo.data = data;

        current_node->next = NULL;

        if (i == 0)
        {
            data->philo_head = current_node;
        }
        else
        {
            previous_node->next = current_node;
        }
        previous_node = current_node;
        i++;
    }
    return 0;
}

int init_mutexes(gen_data *data)
{
    int i;

    // Initialize fork mutexes
    for (i = 0; i < data->num_philosophers; i++)
    {
        if (pthread_mutex_init(&data->fork[i], NULL) != 0)
            return -1;
    }

    // Initialize print lock mutex
    if (pthread_mutex_init(&data->lock, NULL) != 0)
        return -1;

    return 0;
}

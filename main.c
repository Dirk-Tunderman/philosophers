
#include "philo.h"



int main(int argc, char *argv[]) 
{ 
    //args; num-philos, time-to-die, time-to-eat, time-to-sleep, [num of times to eat]

    philo_data *data;
    philos *philos_id;
    
    init_data(argv, data);
    init_forks(data);
    //printf("num-philos: %d\n timetodie: %d\n time-to-eat: %d\ntimetosleep: %d\n", data->num_philosophers, data->time_to_die, data->time_to_eat, data->time_to_sleep);



    return 0;
}





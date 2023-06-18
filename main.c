/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunderm <dtunderm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:00:44 by dtunderm          #+#    #+#             */
/*   Updated: 2023/05/30 14:35:00 by dtunderm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    terminate_threads(gen_data *data)
{
    philo_node *current_node = data->philo_head;
    while (current_node != NULL)
    {
        pthread_join(current_node->philo.thread_id, NULL);
        pthread_join(current_node->philo.death_thread_id, NULL);
        current_node = current_node->next;
    }

    // Free allocated memory and destroy mutexes
    for (int i = 0; i < data->num_philosophers; i++)
    {
        pthread_mutex_destroy(&data->fork[i]);
    }
    pthread_mutex_destroy(&data->lock);
}

void    free_data(gen_data *data)
{
    philo_node *current_node = data->philo_head;

    current_node = data->philo_head;
    while (current_node != NULL)
    {
        philo_node *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }

    free(data->fork);
    free(data);

}

void    leaks(void)
{
    system("leaks");
}

int main(int argc, char *argv[]) 
{ 
    gen_data *data = malloc(sizeof(gen_data));
    if (data == NULL)
        return -1;
    //args; num-philos, time-to-die, time-to-eat, time-to-sleep, [num of times to eat]
    if (argc < 5 || argc > 6)
    {
        printf("Invalid number of arguments.\n");
        return -1;
    }

    if (init_data(argv, data) == -1)
        return -1;

    start_philosopher_threads(data);

    if (data->p_finish == data->num_philosophers)
        EXIT_SUCCESS;

    terminate_threads(data);
    free_data(data);

    atexit(leaks);

    return 0;
}




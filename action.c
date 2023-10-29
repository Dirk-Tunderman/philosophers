/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunderm <dtunderm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:32:13 by dtunderm          #+#    #+#             */
/*   Updated: 2023/05/30 15:35:43 by dtunderm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_philosopher_threads(gen_data *data)
{
    philo_node *current_node = data->philo_head;

    while (current_node != NULL) 
	{
        pthread_create(&current_node->philo.thread_id, NULL, philosopher_action, (void *)&current_node->philo);
        pthread_create(&current_node->philo.death_thread_id, NULL, check_philosopher_death, (void *)&current_node->philo);
        current_node = current_node->next;
    }
}

void *philosopher_action(void *args) 
{

    int i;
    one_philo *philo = (one_philo *)args;
    gen_data *data = philo->data;
    data->beginning_time = timing();
    
    i = 0;
    while (1) 
    {
        // weten bij welke index je moet hebben. 
        // Think
        if (data->done == 1)
                pthread_exit(NULL);
        while (i < data->num_philosophers && data->p_finish != data->num_philosophers)
        {
            if (data->done == 1)
                EXIT_SUCCESS;
            eat(philo);

            sleep_philo(philo);

            think(philo);

        	i = (i + 1) % data->num_philosophers;
    	}
    	return NULL;
	}
}

void eat(one_philo *philo)
{
    gen_data *data = philo->data;
    if (philo->philosopher_id % 2 == 0)
    {
        pthread_mutex_lock(&data->fork[philo->l_fork]);
        printf("%lld\t%d\thas taken a fork\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
        pthread_mutex_lock(&data->fork[philo->r_fork]);
        printf("%lld\t%d\thas taken a fork\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
    }
    else
    {
        pthread_mutex_lock(&data->fork[philo->r_fork]);
        printf("%lld\t%d\thas taken a fork\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
        pthread_mutex_lock(&data->fork[philo->l_fork]);
        printf("%lld\t%d\thas taken a fork\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
    }

    philo->time_last_meal = timing();
    printf("%lld\t%d\tis eating\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
    german_usleep(data->time_to_eat);

    philo->meals_finished++;
    printf("philo: %d has eaten %d times\n", philo->philosopher_id, philo->meals_finished);

    if (philo->meals_finished == data->num_times_must_eat) // if 1 philo finished his meals
    {
        philo->data->p_finish++;
        if (philo->data->p_finish == data->num_philosophers) // if all philos finished their meals
        {
            pthread_mutex_unlock(&data->fork[philo->l_fork]);
            pthread_mutex_unlock(&data->fork[philo->r_fork]);

            return ;
        }
    }

    pthread_mutex_unlock(&data->fork[philo->l_fork]);
    pthread_mutex_unlock(&data->fork[philo->r_fork]);

}

int check_philo_eaten(gen_data *data)
{
    philo_node *current_node = data->philo_head;
    int count = 0;

    while (current_node != NULL) {
        if (current_node->philo.meals_finished >= data->num_times_must_eat)
            count++;
        current_node = current_node->next;
    }

    if (count == data->num_philosophers)
        return 1;
    else
        return 0;
}

void think(one_philo *philo)
{
    if (philo->data->p_finish == philo->data->num_philosophers)
    {
        return ;
    }
    printf("%lld\t%d\tis thinking\n", get_current_time_ms() - philo->data->beginning_time, philo->philosopher_id);
}


void sleep_philo(one_philo *philo)
{
    //gen_data *data = philo->data;
    // if (philo->data->p_finish == philo->data->num_philosophers)
    // {
    //     return ;
    // }
    printf("%lld\t%d\tis sleeping\n", timing() - philo->data->beginning_time, philo->philosopher_id);
    german_usleep(philo->data->time_to_sleep);
}


void *check_philosopher_death(void *args)
{
    one_philo *philo = (one_philo *)args;
    gen_data *data = philo->data;
    while (1)
    {
    if (philo->data->p_finish == philo->data->num_philosophers) // all philo finished eating
    {
        printf("all philos are finished eating\n");
        data->done = 1;
        EXIT_SUCCESS;
    }

    pthread_mutex_lock(&data->lock);
    //long long current_time = time_diff(data->beginning_time, timing());

    if ((philo->time_last_meal - data->beginning_time) > data->time_to_die)
    {
            printf("%lld\t%d\tdied of hunger\n", timing() - data->beginning_time, philo->philosopher_id);
            data->done = 1;
            pthread_exit(NULL);
            
        // pthread_mutex_lock(&data.);
        pthread_mutex_unlock(&data->lock);
        //EXIT_SUCCESS ;// Exit the program if a philosopher dies
    }
    else
        pthread_mutex_unlock(&data->lock);
    }
    return NULL;
}

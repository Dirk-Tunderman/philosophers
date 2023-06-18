/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtunderm <dtunderm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:39:18 by dtunderm          #+#    #+#             */
/*   Updated: 2023/05/30 15:33:27 by dtunderm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time_ms()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}


long long timing()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

long long time_diff(long long start, long long end)
{
    return end - start;
}

void german_usleep(long long sleep_time)
{
	long long				sleep_start;
	sleep_start = timing();

	while (1)
	{
		if (time_diff(sleep_start, timing()) >= sleep_time)
			return ;
		usleep(300);
	}
}

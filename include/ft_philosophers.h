/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/19 11:03:28 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

#include "libft.h"
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

enum	t_state
{
	SLEEP,
	EAT,
	THINK,
};

typedef struct s_table {
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    long start_time;
} t_table;

typedef struct s_philosopher {
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread;
    t_table *table;
} t_philosopher;

#endif
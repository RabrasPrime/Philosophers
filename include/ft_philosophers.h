/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/20 15:08:02 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

#include "libft.h"
#include <pthread.h>
#include "ft_printf.h"
#include <stdlib.h>
#include <sys/time.h>

enum	t_state
{
	SLEEP,
	EAT,
	THINK,
};

typedef struct s_table t_table;

typedef struct s_philosopher {
    int id;
    int left_fork;
    int right_fork;
    long last_meal_time;
    int meals_eaten;
    t_table *table;
    pthread_t thread;
} t_philosopher;

typedef struct s_table {
    int num_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    int stop_simulation;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher *philosophers;
} t_table;

#endif
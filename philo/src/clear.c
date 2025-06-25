/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:50:38 by tjooris           #+#    #+#             */
/*   Updated: 2025/06/25 12:18:49 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void clear_table(t_table *table)
{
    int i;

    if (!table)
        return;
    if (table->forks)
    {
        i = 0;
        while (i < table->num_philosophers)
        {
            pthread_mutex_destroy(&table->forks[i].fork);
            i++;
        }
        free(table->forks);
    }
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->status_simulation);
    pthread_mutex_destroy(&table->init);
    if (table->philosophers)
        free(table->philosophers);
    free(table);
}

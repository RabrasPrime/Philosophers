/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjooris <tjooris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:07:41 by tjooris           #+#    #+#             */
/*   Updated: 2025/03/20 15:10:41 by tjooris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void print_status(t_philosopher *philo, char *message) {
    pthread_mutex_lock(&philo->table->print_lock);
    printf("[%ld] Philosopher %d %s\n", get_time_in_ms(), philo->id, message);
    pthread_mutex_unlock(&philo->table->print_lock);
}

t_table *init_table(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return NULL;
    }

    t_table *table = malloc(sizeof(t_table));
    table->num_philosophers = atoi(argv[1]);
    table->time_to_die = atol(argv[2]);
    table->time_to_eat = atol(argv[3]);
    table->time_to_sleep = atol(argv[4]);
    table->must_eat_count = (argc == 6) ? atoi(argv[5]) : -1;
    table->stop_simulation = 0;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
    table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
    pthread_mutex_init(&table->print_lock, NULL);

    for (int i = 0; i < table->num_philosophers; i++) {
        pthread_mutex_init(&table->forks[i], NULL);
        table->philosophers[i].id = i;
        table->philosophers[i].left_fork = i;
        table->philosophers[i].right_fork = (i + 1) % table->num_philosophers;
        table->philosophers[i].last_meal_time = get_time_in_ms();
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].table = table;
    }
    return table;
}

void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;

    if (philo->id % 2 == 0) { 
        print_status(philo, "is thinking 💭");
        usleep(philo->table->time_to_eat * 1000);
    } else {
        take_forks_and_eat(philo);
    }

    while (!philo->table->stop_simulation) {
        print_status(philo, "is thinking 💭");
        take_forks_and_eat(philo);
    }
    return NULL;
}

void take_forks_and_eat(t_philosopher *philo) {
    t_table *table = philo->table;

    if (philo->id % 2 == 0) { 
        pthread_mutex_lock(&table->forks[philo->left_fork]);
        print_status(philo, "has taken a fork 🍴 (left)");
        pthread_mutex_lock(&table->forks[philo->right_fork]);
        print_status(philo, "has taken a fork 🍴 (right)");
    } else { 
        pthread_mutex_lock(&table->forks[philo->right_fork]);
        print_status(philo, "has taken a fork 🍴 (right)");
        pthread_mutex_lock(&table->forks[philo->left_fork]);
        print_status(philo, "has taken a fork 🍴 (left)");
    }

    print_status(philo, "is eating 🍝");
    philo->last_meal_time = get_time_in_ms();
    philo->meals_eaten++;
    usleep(table->time_to_eat * 1000);

    pthread_mutex_unlock(&table->forks[philo->right_fork]);
    pthread_mutex_unlock(&table->forks[philo->left_fork]);

    print_status(philo, "is sleeping 😴");
    usleep(table->time_to_sleep * 1000);
}

long get_time_in_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void start_simulation(t_table *table) {
    for (int i = 0; i < table->num_philosophers; i++) {
        pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
    }

    for (int i = 0; i < table->num_philosophers; i++) {
        pthread_join(table->philosophers[i].thread, NULL);
    }
}

int main(int argc, char **argv)
{
	t_table *table = init_table(argc, argv);

	if (argc < 5 || argc > 6)
		ft_error("erreur, nombre d'arguments invalide");
	
	for (int i = 0; i < table->num_philosophers; i++)
        pthread_mutex_destroy(&table->forks[i]);
    pthread_mutex_destroy(&table->print_lock);
    free(table->forks);
    free(table->philosophers);
    free(table);
}

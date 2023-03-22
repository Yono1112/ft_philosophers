/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:05:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 14:20:58 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

pthread_mutex_t *forks;
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
int *philosophers;
int num_philosophers;
int time_to_die;
int time_to_eat;
int time_to_sleep;
int num_must_eat = -1;

long get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void print_message(int philosopher_id, char *message)
{
    pthread_mutex_lock(&print_mutex);
    printf("%ld %d %s\n", get_time(), philosopher_id + 1, message);
    pthread_mutex_unlock(&print_mutex);
}

void pick_forks(int philosopher_id)
{
    pthread_mutex_lock(&forks[philosopher_id]);
    print_message(philosopher_id, "has taken a fork");
    pthread_mutex_lock(&forks[(philosopher_id + 1) % num_philosophers]);
    print_message(philosopher_id, "has taken a fork");
}

void put_forks(int philosopher_id)
{
    pthread_mutex_unlock(&forks[philosopher_id]);
    pthread_mutex_unlock(&forks[(philosopher_id + 1) % num_philosophers]);
}

void *philosopher(void *arg)
{
    int philosopher_id = *((int *) arg);
    int num_eaten = 0;
    while (num_must_eat == -1 || num_eaten < num_must_eat)
    {
        print_message(philosopher_id, "is thinking");
        pick_forks(philosopher_id);
        print_message(philosopher_id, "is eating");
        usleep(time_to_eat * 1000);
        put_forks(philosopher_id);
        num_eaten++;
        print_message(philosopher_id, "is sleeping");
        usleep(time_to_sleep * 1000);
    }
    pthread_exit(NULL);
}

// void parse_arguments(int argc, char *argv[])
// {
//     if (argc < 5 || argc > 6)
//     {
//         printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep "
//                "[number_of_times_each_philosopher_must_eat]\n");
//         exit(EXIT_FAILURE);
//     }
//     num_philosophers = atoi(argv[1]);
//     time_to_die = atoi(argv[2]);
//     time_to_eat = atoi(argv[3]);
//     time_to_sleep = atoi(argv[4]);
//     if (argc == 6)
//     {
//         num_must_eat = atoi(argv[5]);
//     }
// }

int main(int argc, char **argv)
{
    pthread_t philosophers[num_philosophers];
    pthread_mutex_init(forks, NULL);
	pthread_mutex_init(&print_mutex, NULL);

    if (argc < 5 || argc > 6)
    {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return 1;
    }
    num_philosophers = atoi(argv[1]);
    time_to_die = atoi(argv[2]);
    time_to_eat = atoi(argv[3]);
    time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        num_must_eat = atoi(argv[5]);

    int *philosopher_ids = malloc(sizeof(int) * num_philosophers);
    for (int i = 0; i < num_philosophers; ++i)
        philosopher_ids[i] = i;

    for (int i = 0; i < num_philosophers; ++i)
    {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
        pthread_detach(philosophers[i]);
    }

    for (int i = 0; i < num_philosophers; ++i)
        pthread_join(philosophers[i], NULL);

    pthread_mutex_init(forks, NULL);
	pthread_mutex_init(&print_mutex, NULL);
    free(philosopher_ids);

    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:57 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/19 14:51:00 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

int main(void)
{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int result = pthread_mutex_destroy(&mutex);

	if (result != 0) {
		char error_msg[1024];
		snprintf(error_msg, sizeof(error_msg), "Error: %s\n", strerror(result));
		write(STDERR_FILENO, error_msg, strlen(error_msg));
		exit(EXIT_FAILURE);
	}

	return 0;
}

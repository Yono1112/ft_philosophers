#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			time;

	if (gettimeofday(&tv, NULL))
		return (0);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	// time = tv.tv_usec / 1000;
	return (time);
}

int main(void)
{
	time_t			start_time;

	start_time = get_time();
	while (1)
	{
		printf("%lu\n", get_time() - start_time);
		// usleep(1000);
	}
	return (0);
}

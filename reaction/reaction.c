#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include <time.h>


void init_led();
void init_button();
void deinit_led();
void deinit_button();

void set_led(int s);
int get_button();

int fd_led;
int fd_btn;

time_t start_time, end_time;
struct timeval *start_t, *end_t;

int ms;

char *str_buf;

int main ()
{
	init_led();
	init_button();

	srand(time(NULL));   // should only be called once


	str_buf = "Hello World!\r\n";
	write(1, str_buf, strlen(str_buf));

	for(int i = 0; i < 5; i++)
	{
		int r = rand();      // returns a pseudo-random integer between 0 and RAND_MAX

		dprintf(1,"Get ready...");
		usleep( (r % 300) * 10000);
		set_led(1);

		start_time = time(NULL);
		start_t = gettimeofday();
		while(get_button() == 1);
		end_t = gettimeofday();
		end_time = time(NULL);

		ms = end_t->tv_sec*1000 + end_t->tv_usec/1000;
		ms -= start_t->tv_sec*1000 + start_t->tv_usec/1000;
		dprintf(1,"Your delay was %d ticks\r\n", ms);

		usleep(1000000);
		set_led(0);

	}


	for(int i = 0; i < 5; i++)
	{
//		system("echo '1' >/sys/class/gpio/gpio200/value");
		set_led(1);
//		system("cat /sys/class/gpio/gpio191/value");
//		if(get_button()) str_buf = "high\r\n";
//		else str_buf = "low\r\n";
//		write(1, str_buf, strlen(str_buf));

		usleep(100000);
//		for(int j = 0; j<1000000; j++) usleep();
//		system("echo '0' >/sys/class/gpio/gpio200/value");
		set_led(0);
//		system("cat /sys/class/gpio/gpio191/value");
//		if(get_button()) str_buf = "high\r\n";
//		else str_buf = "low\r\n";
//		write(1, str_buf, strlen(str_buf));

		usleep(100000);
//		for(int j = 0; j<1000000; j++) usleep();
	}


	deinit_led();
	deinit_button();
	return 0;
}


void init_led()
{
	int fd = -1;
	const void* s;
//	system("echo 200 >/sys/class/gpio/export");
//	system("echo 'out' >/sys/class/gpio/gpio200/direction");

	fd = open("/sys/class/gpio/export", O_WRONLY );
	if(fd != -1)
	{
		s = "200";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("Error openning /sys/class/gpio/export");
		exit(errno);
	}

	fd = open("/sys/class/gpio/gpio200/direction", O_WRONLY );
	if(fd != -1)
	{
		s = "out";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("Error openning /sys/class/gpio/export");
		exit(errno);
	}

	fd_led = open("/sys/class/gpio/gpio200/value", O_RDWR );
	if(fd_led != -1)
	{
		s = "200";
		write(fd, "200", strlen(s));
	}
	else
	{
		perror("Error openning /sys/class/gpio/gpio200/value");
		exit(errno);
	}
}

void init_button()
{
//	system("echo 191 >/sys/class/gpio/export");
//	system("echo 'in' >/sys/class/gpio/gpio191/direction");

	int fd = -1;
	const void* s;

	fd = open("/sys/class/gpio/export", O_WRONLY );
	if(fd != -1)
	{
		s = "191";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("Error openning /sys/class/gpio/export");
		exit(errno);
	}

	fd = open("/sys/class/gpio/gpio191/direction", O_WRONLY );
	if(fd != -1)
	{
		s = "in\n";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("/sys/class/gpio/gpio191/direction");
		exit(errno);
	}

	fd_btn = open("/sys/class/gpio/gpio191/value", O_RDWR );
	if(fd_btn != -1)
	{
	}
	else
	{
		perror("Error openning /sys/class/gpio/gpio191/value");
		exit(errno);
	}
}

void deinit_led()
{
//	system("echo 200 >/sys/class/gpio/unexport");
	int fd = -1;
	const void* s;

	fd = open("/sys/class/gpio/unexport", O_WRONLY );
	if(fd != -1)
	{
		s = "200";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("Error openning /sys/class/gpio/unexport");
		exit(errno);
	}
}

void deinit_button()
{
//	system("echo 191 >/sys/class/gpio/unexport");

	int fd = -1;
	const void* s;

	fd = open("/sys/class/gpio/unexport", O_WRONLY );
	if(fd != -1)
	{
		s = "191";
		write(fd, s, strlen(s));
		close(fd);
	}
	else
	{
		perror("Error openning /sys/class/gpio/unexport");
		exit(errno);
	}

}

void set_led(int s)
{
	if(s) write(fd_led, "1\n", strlen("1\n"));
	else  write(fd_led, "0\n", strlen("0\n"));
}

int get_button()
{
	char s[1];

	lseek(fd_btn, 0, SEEK_SET);
	read(fd_btn, s, 1);

	if(s[0] == '0') return 0;
	if(s[0] == '1') return 1;
	return 0;
}

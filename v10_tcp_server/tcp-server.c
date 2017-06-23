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

int fd;
char s[100];

int main ()
{
  dprintf(1,"Hello\r\n");
  fd = open("/tmp/mod_hrtimer", O_RDONLY );

  read(fd, s, 100);
  dprintf(1,">>%s\r\n",s);

  return 0;
}


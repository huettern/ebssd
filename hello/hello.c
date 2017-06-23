#include <stdio.h>
#include <unistd.h>


int main () {
	char hname[20];
	gethostname(hname, 20);
	printf("Hostname=%s\r\n",hname);
	return 0;
}


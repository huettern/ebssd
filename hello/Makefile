
APP=hello

CC=arm-linux-gnueabihf-gcc
SIZE=arm-linux-gnueabihf-size
GDB=arm-linux-gnueabihf-gdb

CFLAGS  =-mthumb -march=armv7-a
CFLAGS += -g -Wall

all: $(APP)

install: all
	scp $(APP) root@192.168.2.20:/usr/bin/

run: install
	@echo ------------------------------------
	@ssh root@192.168.2.20 /usr/bin/$(APP) ||:

debug: install
	ssh root@192.168.2.20 gdbserver :2000 /usr/bin/$(APP)
#	$(GDB) -tui $(APP)

hello: hello.c
	$(CC) $(CFLAGS) -o $(APP) $(APP).c
	$(SIZE) $(APP)ma

clean:
	rm -f $(APP)

.PHONY: clean


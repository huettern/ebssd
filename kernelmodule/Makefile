obj-m = mod_hello.o
KERNEL_SRC = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules
	rm -f *.o *.mod.c modules.order Module.symvers

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean

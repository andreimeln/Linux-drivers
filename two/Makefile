.PHONY: default clean

CURRENT := $(shell uname -r)
KDIR := /lib/modules/$(CURRENT)/build
PWD := $(shell pwd)

obj-m := one.o two.o

one-objs := one_init.o one_func.o

two-objs := two_start.o two_stop.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c
	rm *.symvers *.order

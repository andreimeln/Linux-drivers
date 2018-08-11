.PHONY: default clean

CURRENT := $(shell uname -r)
KDIR := /lib/modules/$(CURRENT)/build
PWD := $(shell pwd)

obj-m := multi.o

multi-objs := start.o stop.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.o *.ko *.mod.c
	rm *.symvers *.order

.PHONY: default clean

CURRENT := $(shell uname -r)
KDIR := /lib/modules/$(CURRENT)/build
PWD := $(shell pwd)

obj-m := params.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# KDIR - current folder of build
# M - where to go after build

clean:
	rm -f *.o *.ko *.mod.c *.symvers *.order

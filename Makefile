obj-m += test_printk.o test_used.o

all:
        make --directory /lib/modules/$(shell uname --kernel-release)/build M=$(PWD) modules

clean:
        make --directory /lib/modules/$(shell uname --kernel-release)/build M=$(PWD) clean

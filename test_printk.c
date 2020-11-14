#include <linux/init.h>
#include <linux/module.h>
#include "test_used.h"

MODULE_LICENSE("GPL");

static int __init test_printk_init(void) {
	printk(KERN_INFO "primary module inserted\n");
	printk(KERN_INFO "param from used module: %s\n", data_from_param);
	return 0;
}
static void __exit test_printk_exit(void) {
	printk(KERN_INFO "primary module removed\n");
}

module_init(test_printk_init);
module_exit(test_printk_exit);

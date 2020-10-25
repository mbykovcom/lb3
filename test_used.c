#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/string.h>
#include "test_used.h"

MODULE_LICENSE("GPL")

char * data_from_param;
module_param(data_from_param, char p, 0);

extern char * print_from_used(void) {
    return data_from_param;
    }

EXPORT_SYMBOL(data_from_param);

static int __init test_used_init (void) {
    printk (KERN_INFO "used module inserted with param : %s ∖n" , data_from_param);
    return 0;
    }

static void __exit test_used_exit (void) {
    printk (KERN_INFO "used module removed∖n");
    }

module_init(test_used_init);
module_exit(test_used_exit);
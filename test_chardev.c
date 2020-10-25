/* test */
#include <linux/init.h>
#include <linuc/module.h>
#include <lilinux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
#define MODULE_NAME "test_chardev"
static char * test_data = "test∖n";
static int dev_counter = 0 ;
static int major ;
static int chardev_open(struct inode *, struct file *);
static int chardev_release(struct inode *, struct file * );
static ssize_t chardev_wrire (struct file *, const char *, size_t , loff_t *);
static ssize_t chardev_read (struct file *, char *,  size_t , loff_t *);

static struct file_operations chardev_operations = {
        .read = chardev_read,
        .write = chardev_wrire,
        .open = chardev_open,
        .release =chardev_release
};

static int chardev_open(struct inode * inode, struct file * file) {
    if (dev_counter) return −EBUSY;
    dev_counter++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int chardev_release(struct inode * inode , struct file * file) {
    dev_counter−−;
    module_put(THIS_MODULE) ;
    return 0;
}

static ssize_t chardev_read(struct file * file, char * buf , size_t count, loff_t * off) {
int test_data_lenght = strlen(test_data);
    if (* off != 0) return 0;
    if (copy_to_user(buf, test_data, test_data_lenght)) return −EINVAL;
    * off = test_data_lenght;
    return test_data_lenght;
}

static ssize_t chardev_write(struct file * file, char * buf , size_t count, loff_t * off) {
    printk(KERN_ERR "Error: read only device ∖n");
    return −EINVAL;
}

static int __init test_chardev_init(void) {
    major = register_chrdev(0 , "test_chardev", &chardev_operations) ;
    printk(KERN_INFO "loaded major dev %d∖n", major );
    return 0;
}

static int __exit test_chardev_exit(void) {
    unregister_chrdev(major, MODULENAME);
    printk(KERN_INFO "removed∖n");
}

module_init(test_chardev_init);
module_exit(test_chardev_exit);
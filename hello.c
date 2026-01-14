#include <linux/init.h>
#include <linux/module.h>
static int init() { printk("hello world"); }
static void exit() { printk("exiting the program"); }
module_init(init);
module_exit(exit);

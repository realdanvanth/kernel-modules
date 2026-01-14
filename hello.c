#include <linux/init.h>
#include <linux/module.h>
static int __init init(void) {
  printk("hello world");
  return 0;
}
static void __exit exit(void) { printk("exiting the program"); }
module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#define DEVICE "hello"
static int major;
static int open(struct inode *inode, struct file *filp) {
  printk("file opened\n");
  printk("major : %d minor: %d\n", imajor(inode), iminor(inode));
  printk("mode : %x\n", filp->f_mode);
  return 0;
}
static int release(struct inode *, struct file *) {
  printk("file released\n");
  return 0;
}
static ssize_t read(struct file *, char __user *, size_t, loff_t *) {

  return 0;
}
ssize_t write(struct file *, const char __user *, size_t, loff_t *) {

  return 0;
}
static struct file_operations fops = {.open = open, .release = release};
static int __init init(void) {
  printk("module initialized\n");
  register_chrdev(major, DEVICE, &fops);
  return 0;
}
static void __exit exit(void) {
  unregister_chrdev(major, DEVICE);
  printk("module removed\n");
}
module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");

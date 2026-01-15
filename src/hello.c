#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#define DEVICE "hello"
static int major;
static char data[256];
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
static ssize_t read(struct file *filep, char __user *user, size_t l,
                    loff_t *off) {
  size_t index = l + *off;
  if (*off >= sizeof(data)) {
    return 0;
  } else if (index >= sizeof(data)) {
    l = sizeof(data) - *off;
  }
  if (copy_to_user(user, &data[*off], l))
    return 0;
  printk("read\n");
  *off += l;
  return l;
}
ssize_t write(struct file *filep, const char __user *user, size_t l,
              loff_t *off) {
  size_t index = l + *off;
  if (*off >= sizeof(data)) {
    return 0;
  } else if (index >= sizeof(data)) {
    l = sizeof(data) - *off;
  }
  if (copy_from_user(&data[*off], user, l)) {
    return 0;
  }
  *off = *off + l;
  printk("written\n");
  return l;
}
static struct file_operations fops = {
    .open = open, .release = release, .read = read, .write = write};
static int __init init(void) {
  printk("module initialized\n");
  major = register_chrdev(0, DEVICE, &fops);
  printk("major: %d\n", major);
  return 0;
}
static void __exit exit(void) {
  unregister_chrdev(major, DEVICE);
  printk("module removed\n");
}
module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");

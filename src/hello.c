#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>
#define DEVICE "vicharak"
#ifndef MY_IOCTL
#define MY_IOCTL
struct data {
  int length;
  char *data;
};
#define SET_SIZE_OF_QUEUE _IOW('a', 'a', int *)
#define PUSH_DATA _IOW('a', 'b', struct data *)
#define POP_DATA _IOR('a', 'c', struct data *)
#endif
static int size;
static char *buffer;
static int major;
static DEFINE_MUTEX(lock);
static long ioctl(struct file *filp, unsigned int cmd, unsigned long args) {
  int status = 0;
  mutex_lock(&lock);
  struct data buff;
  switch (cmd) {
  case SET_SIZE_OF_QUEUE: {
    status = copy_from_user(&size, (int *__user)args, sizeof(int));
    pr_info("ARRAY INITIALIZED WITH SIZE %d\n", size);
    kfree(buffer);
    buffer = kmalloc(size, GFP_KERNEL);
    mutex_unlock(&lock);
    break;
  } break;
  case PUSH_DATA: {
    status = copy_from_user(&buff, (struct data *)args, sizeof(buff));
    status = copy_from_user(buffer, (int *)buff.data, buff.length);
    pr_info("buffer got %s\n", buffer);
    mutex_unlock(&lock);
    break;
  } break;
  case POP_DATA: {
    status = copy_from_user(&buff, (struct data *)args, sizeof(buff));
    status = copy_to_user(buff.data, buffer, buff.length);
    pr_info("buffer sent\n");
    mutex_unlock(&lock);
  } break;
  }
  return 0;
}
static struct file_operations fops = {.unlocked_ioctl = ioctl};
static int __init init(void) {
  major = register_chrdev(0, DEVICE, &fops);
  pr_info("MODULE INITIALIZE %d\n", major);
  return 0;
}
static void __exit exit(void) {
  unregister_chrdev(major, DEVICE);
  pr_info("MODULE RELEASED\n");
}
module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");

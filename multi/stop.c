#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vasya Pupkin <pupkin@mail.ru>");

void cleanup_module(void)
{
  printk(KERN_ALERT "Module 'multi' stopped\n");
}

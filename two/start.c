#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vasya Pupkin <pupkin@mail.ru>");

int __init init_module(void)
{
  printk(KERN_ALERT "Module 'multi' started\n");
  return 0;
}

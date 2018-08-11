#include <linux/kernel.h>
#include <linux/module.h>

#include "one.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vasya Pupkin <pupkin@mail.ru>");

int __init init_module(void)
{
  printk(KERN_ALERT "Module 'two' started\n");
  one_report("Hello!");
  return 0;
}

module_init(init_module);

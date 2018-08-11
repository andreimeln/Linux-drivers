#include <linux/kernel.h>
#include <linux/module.h>

void __exit module_cleanup(void)
{
  printk(KERN_ALERT "Module 'two' stopped\n");
}

module_exit(module_cleanup);

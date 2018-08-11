#include <linux/kernel.h>
#include <linux/module.h>

void one_report(char *text)
{
  printk(KERN_ALERT "Reported: %s\n", text);
}

EXPORT_SYMBOL(one_report);

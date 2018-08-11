#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vasya Pupkin <pupkin@mail.ru>");

static short int par1 = 1;
module_param(par1, short, 0644);
MODULE_PARM_DESC(par1, "A short integer");

static char *par2 = "Hello, world!" ;
module_param(par2, charp, 0644); // charp - macros for "*char"
MODULE_PARM_DESC(par1, "A text parameter");

int __init init_module(void)
{
  printk(KERN_ALERT "Module started\n");
  printk(KERN_ALERT "par1 = %hd\n", par1);
  printk(KERN_ALERT "par2 = %s\n", par2);
  return 0;
}

//static
void __exit cleanup_module(void)
{
  printk(KERN_ALERT "Module stopped\n");
}

//module_init(hello_init);
//module_exit(hello_exit);

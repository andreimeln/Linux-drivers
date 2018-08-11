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

static struct file_operations fops = {

.owner = THIS_MODULE //,
  //.read = proc_read
};

static struct proc_dir_entry *pde = 0;

int __init init_module(void)
{
  printk(KERN_ALERT "Module started\n");
  printk(KERN_ALERT "par1 = %hd\n", par1);
  printk(KERN_ALERT "par2 = %s\n", par2);

  pde = proc_create(PROC_ITEM_NAME, 0644|S_IFREG, NULL, &fops);
  if (!pde)
    {
      printk(KERN_ALERT "Cannot create proc entry\n");
      return -ENOMEM;
    }

  printk(KERN_ALERT "Proc entry created\n");
  
  return 0;
}

void __exit cleanup_module(void)
{
  remove_proc_entry(PROC_ITEM_NAME, NULL);
  printk(KERN_ALERT "Module stopped\n");
}

//module_init(hello_init);
//module_exit(hello_exit);

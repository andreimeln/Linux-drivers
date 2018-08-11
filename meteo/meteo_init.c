#include <linux/slab.h>

#include "meteo.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author");

static int major = 0;
module_param(major, int, 0644);
MODULE_PARM_DESC(major, "Major device number");

static int count = 1;
module_param(count, int, 0644);
MODULE_PARM_DESC(count, "Count of item blocks");

static struct file_operations fops = {

  .open = meteo_open,
  .release = meteo_release,
  .read = meteo_read,
  .write = meteo_write
  //.llseek = meteo_llseek;
};

int __init init_module()
{
  int RetCode = 0;
  //int k;
  
  if (count < 1 || count > 256)
    {
      RetCode = -EINVAL;
      goto END;
    }
  
  {
    // allocate memory
    AllDev = (struct meteo_group *)
              kmalloc(sizeof(struct meteo_group)*count,
	              GFP_KERNEL);
    if (! AllDev)
      {
	printk(KERN_ALERT "'meteo': out of memory (1)\n");
	RetCode = -ENOMEM;
	goto END; // throw in C++
      }
    // always fill allocated memory with zeros
    memset(AllDev, 0, count*sizeof(struct meteo_group*));
    AllCount = count;
  }
  {
    int M = register_chrdev(major, METEO_NAME, &fops);
    if (M < 0) // major < 0
      {
	//printk(KERN_ALERT "Error: %d\n", major);
	//return major;
	printk(KERN_ALERT "Error: %d\n", M);
	//return M;
	RetCode = M;
	goto END1;
      }
    else if (major == 0)
      {
	major = M;
      }
  }

  // there might be something else here
  
  printk(KERN_ALERT "'%s' registered with number %d\n", METEO_NAME, major);

  return 0;

  // Uncomment if/when something is above
  //END2:
  //unregister_chrdev(major, METEO_NAME);

// labels have no offset
END1:
  kfree(AllDev);

END:
  return RetCode;
}

void __exit cleanup_module()
{
  //int k;
  
  unregister_chrdev(major, METEO_NAME);

  kfree(AllDev);

  printk(KERN_ALERT "'%s' unregistered\n", METEO_NAME);
}

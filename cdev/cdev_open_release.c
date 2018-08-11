#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/fs.h>
#include <linux/slab.h>

#include "cdev.h"

#define START_TEXT "Hello, world!!!"

int cdev_open (struct inode *inode, struct file *file)
{
  if (MINOR(inode->i_rdev) > 0)
    return -ENOENT; // no such file; ENODEV - no such device (??)

  if (DevOpened)
    return -EBUSY; // device busy

  if (! try_module_get(THIS_MODULE))
    {
      printk(KERN_ALERT "Cannot lock module\n");
      return -EACCES;
    }

  DevContSize = strlen(START_TEXT); // strlen(DevContents);
  DevContents = (char *)kmalloc(DevContSize+1, GFP_KERNEL);
  if (!DevContents)
    {
      printk(KERN_ALERT "Out of memory\n");
      DevContSize = 0;
      return -ENOMEM;
    }
  //memset(DevContents, 0, DevContSize+1); // good to fill mem with zeros first
  //strncpy(DevContents, START_TEXT, DevContSize+1); // +'\0'
  strcpy(DevContents, START_TEXT);
  // strcpy because memory is already checked, and strcpy is much faster
    
  DevOpened = 1;

  printk(KERN_ALERT "Device opened\n");

  return 0; // SUCCESS;
}

int cdev_release(struct inode *inode, struct file *file)
{
  kfree(DevContents);
  DevContents = 0;
  DevContSize = 0;
  DevOpened = 0;
  printk(KERN_ALERT "Device closed\n");

  module_put(THIS_MODULE);

  return 0;
}

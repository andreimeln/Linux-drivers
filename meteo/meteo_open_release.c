#include "meteo.h"

// minor num of device
#define MIN MINOR(inode->i_rdev)

int meteo_open (struct inode *inode, struct file *file)
{
  int RetCode = 0;
  
  if (MIN >= AllCount)
    {
      // device doesn't exist
      RetCode = -ENOENT;
      goto END;
    }

  if (! try_module_get(THIS_MODULE))
    {
      printk(KERN_ALERT "Cannot lock module\n");
      RetCode = -EACCES;
      goto END;
    }

  // check here if device is not already opened
  
  printk(KERN_ALERT "Device opened\n");

  return 0; // SUCCESS;

END2:
  // remove garbage after device check, if any

END1:
  module_put(THIS_MODULE);

END:
  return RetCode;
}

int meteo_release(struct inode *inode, struct file *file)
{

  // place reset parameters here
  module_put(THIS_MODULE);

  printk(KERN_ALERT "Device closed\n");

  return 0;
}

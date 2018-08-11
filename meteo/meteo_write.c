#include <linux/sched.h>
#include <linux/kthread.h>
#include <asm/uaccess.h>

#include "meteo.h"

#define MIN MINOR(file->f_inode->i_rdev)

int meteo_item_dispatcher(void *data)
{
  struct meteo_item *Dt = (struct meteo_item *)data;
  if (!Dt)
    return -ENOENT;

  try_module_get(THIS_MODULE);
  Dt->f_status = METEO_ACTIVE;

  while (!kthread_should_stop())
    {
      //...
      printk(KERN_ALERT "Step counted\n");
      schedule_timeout_interruptible(1000); // ms
    }

  module_put(THIS_MODULE);
  Dt->f_status = METEO_INACTIVE;
  return 0;
}

ssize_t meteo_write(struct file *file,
		  const char __user *buffer,
		  size_t length,
		  loff_t *ofs)
{
  int ItemNo = 0;
  int ItemCount = 0;
  int k;
  
  if (length == 0) // can't be < 0 - size_t is unsigned
    return 0;	  // nothing supposed to be read

  if (*ofs < 0)
    {
      printk(KERN_ALERT "Negative offset\n");
      return -EIO;
    }

  if (length % sizeof(struct meteo_item) > 0)
    {
      printk(KERN_ALERT "Invalid length\n");
      return -EINVAL;
    }

  ItemCount = length / sizeof(struct meteo_item);

  if (*ofs % sizeof(struct meteo_item) > 0)
    {
      printk(KERN_ALERT "Invalid offset\n");
      return -EIO;
    }

  ItemNo = *ofs / sizeof(struct meteo_item);
  if (ItemNo + ItemCount > METEO_COUNT)
    {
      printk(KERN_ALERT "Invalid item number\n");
      return -EIO;
    }

  // check if we're allowed to write

  for (k = 0; k < ItemCount; k++)
    {
      //struct meteo_item X;
      copy_from_user(&(AllDev[MIN].Buffer),
		     buffer + k * sizeof(struct meteo_item),
		     sizeof(struct meteo_item));
      if (AllDev[MIN].Items[ItemNo+k].f_status ==
	  AllDev[MIN].Buffer.f_status)
	continue;
      if (AllDev[MIN].Buffer.f_status == METEO_ACTIVE)
	{
	  AllDev[MIN].Threads[ItemNo+1] = kthread_run(
					     meteo_item_dispatcher,
					     (void *)(AllDev[MIN].Items+ItemNo+k),
					     "meteo%dn%d", (int)(MIN), ItemNo+1);
	} else
	{
	  kthread_stop(AllDev[MIN].Threads[ItemNo+1]);
	  // wait until thread stops
	  AllDev[MIN].Threads[ItemNo+1] = 0;
	}
      // to launch or stop a thread
    }
  
  printk(KERN_ALERT "%lu bytes written\n", length);

  return length;
}

/*
loff_t cdev_llseek(struct file *file, loff_t ofs, int whence)
{
  switch(whence)
    {
    case SEEK_CUR:
      file->f_pos += ofs;
      break;
      
    case SEEK_SET:
      file->f_pos = ofs;
      break;
      
    case SEEK_END:
      file->f_pos = DevContSize + ofs;
      break;

    default:
      return -EINVAL;
    }

  return 0;
}
*/

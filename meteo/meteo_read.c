#include <asm/uaccess.h>

#include "meteo.h"

#define MIN MINOR(file->f_inode->i_rdev)

ssize_t meteo_read(struct file *file,
		  char *buffer,
		  size_t length,
		  loff_t *ofs)
{

  int ItemNo = 0;
  int ItemCount = 0;
  
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

  // check here if reading is allowed
  
  copy_to_user(buffer, AllDev[MIN].Items + ItemNo, length);
  // current position is deliberately left unchanged

  printk(KERN_ALERT "%lu bytes read\n", length);

  return length;
}

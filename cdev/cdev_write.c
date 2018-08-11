#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#include "cdev.h"

ssize_t cdev_write(struct file *file,
		  const char __user *buffer,
		  size_t length,
		  loff_t *ofs)
{

  if (file->f_mode & O_ACCMODE ==0)
    return -EPERM;

  if (length == 0)
    return 0;	  

  if (*ofs < 0)
    return -EIO;

  if (*ofs + length > DevContSize)
    {
      size_t NewSize = *ofs + length;
      char *N = kmalloc(NewSize+1, GFP_KERNEL);
      if (!N)
	{
	  printk(KERN_ALERT "Out of memory\n");
	  return -ENOMEM;
	}
      memset(N, 0, NewSize + 1);
      strcpy(N, DevContents);
      kfree(DevContents);
      DevContents = N;
      DevContSize = NewSize;
      printk(KERN_ALERT "Memory expanded\n");
    }

  copy_from_user(DevContents+*ofs, buffer, length);
  *ofs += length; // mode offset to the next part of memory

  printk(KERN_ALERT "%lu bytes written\n", length);

  return length;
}

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

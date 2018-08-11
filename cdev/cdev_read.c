#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "cdev.h"

//struct mydata D;
// int R = read (fd, &D, sizeof(D)); // 0 - offset

ssize_t cdev_read(struct file *file,
		  char *buffer,
		  size_t length,
		  loff_t *ofs)
{
  if (length == 0) // can't be < 0 - size_t is unsigned
    return 0;	  // nothing supposed to be read

  if (*ofs < 0)
    return -EIO;

  if (*ofs >= DevContSize)
    return 0;

  if (*ofs + length > DevContSize)  // to read more than what's left
    length = DevContSize - *ofs;  
  
  //memcpy(buffer, DevContents, length);
  copy_to_user(buffer, DevContents+*ofs, length);
  *ofs += length; // mode offset to the next part of memory

  printk(KERN_ALERT "%lu bytes read\n", length);

  return length;
}

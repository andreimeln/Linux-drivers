#ifndef CDEV_H
#define CDEV_H

extern char *DevContents;
extern size_t DevContSize;
extern int DevOpened;

int cdev_open (struct inode *inode, struct file *file);
int cdev_release(struct inode *inode, struct file *file);
ssize_t cdev_read(struct file *file, char *buffer, size_t length, loff_t *ofs);
ssize_t cdev_write(struct file *file, const char __user *buffer, size_t length, loff_t *ofs);
loff_t cdev_llseek(struct file *file, loff_t ofs, int whence);

#endif // CDEV_H

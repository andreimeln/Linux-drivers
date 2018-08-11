#ifndef METEO_H
#define METEO_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#include "meteo_dev.h"

struct meteo_group
{
  struct meteo_item Buffer;
  struct task_struct *Threads[METEO_COUNT];
  struct meteo_item Items[METEO_COUNT];
};

extern struct meteo_group *AllDev;
extern size_t AllCount;

int meteo_open (struct inode *inode, struct file *file);
int meteo_release(struct inode *inode, struct file *file);
ssize_t meteo_read(struct file *file, char *buffer, size_t length, loff_t *ofs);
ssize_t meteo_write(struct file *file, const char __user *buffer, size_t length, loff_t *ofs);
//loff_t meteo_llseek(struct file *file, loff_t ofs, int whence);

#endif // METEO_H

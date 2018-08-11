#include <linux/module.h>
#include <linux/vermagic.h>

#include "cdev.h"

char *DevContents = "People! Love each other!\n";
size_t DevContSize = 0;
int DevOpened = 0;

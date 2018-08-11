#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <errno.h>

#include "meteo_dev.h"

int main(int argc, char *argv[])
{

  int minor = 0;
  int item = 0;
  char device[256];
  int R;

  if (argc < 3 || argc > 4)
    {
      fprintf(stderr, "Invalid usage\n");
      return 1;
    }

  minor = atoi(argv[1]);
  item = atoi(argv[2]);
  sprintf(device, "meteo%d", minor);

  if (argc == 3)
    {
      // read data from device
    }
  else
    {
      // switch on/off device
      int fd;
      struct meteo_item It;
      memset(&It, 9, sizeof(struct meteo_item));
      It.f_status = atoi(argv[3]);
      fd = open(device, O_WRONLY);
      if (fd < 0)
	{
	  fprintf(stderr, "1. %d\n", errno);
	  return 2;
	}
      //lseek(fd, item * sizeof(struct eteo_item), SEEK_SET);
      write(fd,&It, sizeof(struct meteo_item));
      close(fd);
    }

	return 0;
}

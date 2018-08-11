#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

  int k;

  int fd = open("cdev0", O_RDONLY);
  if (fd < 0)
    {
      fprintf(stderr, "Error opening device %d\n", errno);
      return fd;
    }

  for (k = 0; k < 100; k++)
    {
      char B[10];
      int R;
      memset(B,0,10);
      R = read(fd, B, 5);
      if (R < 0)
	{
	  fprintf(stderr,"Error reading device %d\n", errno);
	  return R;
	}
      else if (R == 0)
	break;

      printf("[%s]\n", B);
      sleep(1);
    }

  close(fd);
}

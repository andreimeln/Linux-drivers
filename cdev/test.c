#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{

  int R;
  char Buf[1024];

  int fd = open("cdev0", O_RDWR); // O_RDONLY);
  if (fd < 0)
    {
      fprintf(stderr, "Error opening device %d\n", errno);
      return fd;
    }

  R = read(fd, Buf, 5);
  printf("1. [%s] %d\n", Buf, R);

  R = lseek(fd, 5, SEEK_CUR); // skip first 5 symbols
  printf("2. [%s] %d\n", Buf, R);

  R = read(fd, Buf, 5);
  printf("3. [%s] %d\n", Buf, R);

  R = write(fd, "12345", 5);
  printf("4. %d\n", R);
  
  R = lseek(fd, 5, SEEK_SET);
  printf("5. %d\n", R);

  R = read(fd, Buf, 1023);
  printf("6. [%s] %d\n", Buf, R);  

  close(fd);
}

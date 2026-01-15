#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv) {
  int fd;
  if (argc < 2) {
    printf("nah");
  }
  fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    printf("FD error");
  }
  close(fd);
}

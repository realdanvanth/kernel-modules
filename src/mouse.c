#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  int fd =
      open("/dev/input/by-id/usb-SIGMACHIP_Usb_Mouse-event-mouse", O_RDONLY);
  char buffer[1024];
  int pos = 0;
  struct input_event ev;
  printf("file %d\n", fd);
  while (1) {
    ssize_t n = read(fd, &ev, sizeof(ev));
    if (n != sizeof(ev))
      continue;
    if (ev.type == EV_KEY) {
      if (ev.value == 0) {
        printf("%d \n", ev.code);
      }
    }
  }
}

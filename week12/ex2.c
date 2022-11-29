#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main(int argc, char *argv[]) {
  int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY); 
  struct input_event ev;

  for(;;) {
    size_t n = read(fd, &ev, sizeof(ev));
    if(n != sizeof(ev)) {
      break;
    }

    if(ev.type == EV_KEY) {
      switch(ev.value) {
        case 0:
          printf("\rPRESSED 0x%04x (%d)\n", ev.code, ev.code);
          break;
        case 1:
          printf("\rRELEASED 0x%04x (%d)\n", ev.code, ev.code);
          break;
      }
    }
  }

  return 0;
}

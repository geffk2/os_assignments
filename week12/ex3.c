#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main(int argc, char *argv[]) {
  int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY); 
  struct input_event ev;
  unsigned short pressed_keys = 0;
  unsigned const short EP = KEY_E | KEY_P; 
  unsigned const short CAP = KEY_C | KEY_A | KEY_P;

  for(;;) {
    size_t n = read(fd, &ev, sizeof(ev));
    if(n != sizeof(ev)) {
      break;
    }

    if(ev.type == EV_KEY) {
      switch(ev.value) {
        case 2:
        case 0:
          pressed_keys |= ev.code;
          break;
        case 1:
          pressed_keys ^= ev.code;
          break;
      }
    }


    if(pressed_keys == EP) {
      printf("Exam Passed!\n");
      // pressed_keys ^= EP;
    }

    if(pressed_keys == CAP)) {
      printf("Get some cappuccino!\n");
      // pressed_keys ^= CAP;
    }
  }

  return 0;
}


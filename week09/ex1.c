#include <stdio.h>
#include <stdlib.h>
#define BITS_INC (0b10000000)

typedef struct Page {
  int index;
  int bits;
} Page;

int main (int argc, char *argv[])
{
  Page *frame;
  FILE* fin = fopen("input.txt", "r");
  int n;
  printf("Input size of page frame: ");
  scanf("%d", &n);
  int hits = 0, total = 0;

  frame = calloc(n, sizeof(Page));
  int filled = 0;
  
  while(!feof(fin)) {
    Page buf;
    fscanf(fin, "%d", &buf.index);

    if(feof(fin))
      break;

    buf.bits = BITS_INC;
    total++;

    int found = 0;

    int minBits = BITS_INC << 1;
    int minI = 0;

    for(int i = 0; i < filled; i++) {
      frame[i].bits >>= 1;

      if(frame[i].bits < minBits) {
        minBits = frame[i].bits;
        minI = i;
      }

      if(frame[i].index == buf.index) {
        frame[i].bits |= BITS_INC;
        found = 1;
        hits++;
      }
    }
    if(found)
      continue;
    
    if(filled < n) {
      frame[filled++] = buf;
      continue;
    }
    
    frame[minI] = buf;
  }

  fclose(fin);
  printf("Hit/miss ratio: %f\nHits: %d\nMisses: %d\n", hits / (float) (total - hits), hits, total - hits);
  free(frame);
  return 0;
}

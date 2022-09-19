#include <stdio.h>
#include <math.h>

typedef struct {
  float x, y;
} Point;

float distance(Point a, Point b) {
  return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

float area(Point a, Point b, Point c) {
  return 0.5 * fabs(a.x * b.y - b.x * a.y + b.x * c.y - c.x * b.y + c.x * a.y - a.x * c.y);
}

int main(int argc, char* argv[])
{
  Point a = {.x = 2.5, .y = 6};
  Point b = {.x = 1, .y = 2.2};
  Point c = {.x = 10, .y = 6};

  float d = distance(a, b);
  float S = area(a, b, c);

  printf("Distance: %f\nArea: %f", d, S);

  return 0;
}

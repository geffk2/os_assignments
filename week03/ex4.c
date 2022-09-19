#include <stdio.h>
#include <stdlib.h>

void* addInt(const void* a, const void* b) {
  int* res = malloc(sizeof(int));
  *res = *(int*)a + *(int*)b;
  free(a);
  return res;
}
void* addDouble(const void* a, const void* b) {
  double* res = malloc(sizeof(double));
  *res = *(double*)a + *(double*)b;
  free(a);
  return res;
}
void* mulInt(const void* a, const void* b) {
  int* res = malloc(sizeof(int));
  *res = *(int*)a * *(int*)b;
  free(a);
  return res;
}
void* mulDouble(const void* a, const void* b) {
  double* res = malloc(sizeof(double));
  *res = *(double*)a * *(double*)b;
  free(a);
  return res;
}

typedef struct ParallelMeanInt {
  int n;
  int sum;
} IMean;
typedef struct ParallelMeanDouble {
  int n;
  double sum;
} DMean;
void* meanInt(const void* a, const void* b) {
  const IMean* a1 = a;
  int n = a1->n;
  int s = a1->sum;
  int b1 = *(int*) b;
  IMean* res = malloc(sizeof(IMean));
  res->n = n + 1; 
  res->sum = s + b1;

  free(a);
  return res;
}
void* meanDouble(const void* a, const void* b) {
  const DMean* a1 = a;
  int n = a1->n;
  double s = a1->sum;
  double b1 = *(double*) b;
  DMean* res = malloc(sizeof(DMean));
  res->n = n + 1; 
  res->sum = s + b1;

  free(a);
  return res;
}

void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {
  void* v = initial_value;
  for(int i = 0; i < n; i++) {
    v = opr(v, base + size * i);
  }
  return v;
}

int main(int argc, char* argv[])
{
  int arr1[5] = {1, 2, 3, 4, 5};

  int* i_init = malloc(sizeof(int)); *i_init = 0;
  int* sum = aggregate(arr1, sizeof(int), 5, i_init, addInt);

  i_init = malloc(sizeof(int)); *i_init = 1;
  int* mul = aggregate(arr1, sizeof(int), 5, i_init, mulInt);

  printf("Int:\nSum: %d Mul: %d\n", *sum, *mul);
  
  IMean* mean_init_int = malloc(sizeof(IMean));
  mean_init_int->n = 0;
  mean_init_int->sum = 0;
  IMean* int_mean_res = aggregate(arr1, sizeof(int), 5, mean_init_int, meanInt);
  printf("Mean:%f\n", (double)int_mean_res->sum / int_mean_res->n);

  free(sum);
  free(mul);
  free(int_mean_res);

  double arr2[5] = {1.3, 2.1, 3.2, 4.7, 5.0};

  double* d_init = malloc(sizeof(double)); *d_init = 0;
  double* d_sum = aggregate(arr2, sizeof(double), 5, d_init, addDouble);

  d_init = malloc(sizeof(double)); *d_init = 1;
  double* d_mul = aggregate(arr2, sizeof(double), 5, d_init, mulDouble);

  printf("Double:\nSum: %f Mul: %f\n", *d_sum, *d_mul);
  
  DMean* mean_init_double = malloc(sizeof(DMean));
  mean_init_double->n = 0;
  mean_init_double->sum = 0.0;

  DMean* double_mean_res = aggregate(arr2, sizeof(double), 5, mean_init_double, meanDouble);
  printf("Double mean:%f\n", double_mean_res->sum / double_mean_res->n);

  free(d_sum);
  free(d_mul);
  free(double_mean_res);
  return 0;
}


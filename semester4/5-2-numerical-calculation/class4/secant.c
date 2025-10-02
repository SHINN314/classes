#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// 最小誤差の定義
#define Epsilon ( 1e-14 )

double scant(double (*f)(double), double initial_x0, double initial_x1, double epsilon) {
  // 初期値の定義
  double x0 = initial_x0;
  double x1 = initial_x1;
  double x2 = x1;
  int counter = 0;

  // 漸化式による値の更新
  while(fabs(f(x2)) > epsilon) {
    printf("%d: %1.16f\n", counter, x2);
    x2 = x1 - f(x1)*(x1 - x0) / (f(x1) - f(x0));
    x0 = x1;
    x1 = x2;
    counter++;
  }

  return x2;

}

int main() {
  double f(double x) {
    return sin(x);
  }

  double initial_x0 = 2.0;
  double initial_x1 = 2.1;
  double x2 = scant(f, initial_x0, initial_x1, Epsilon);

  printf("answer = %1.16f\n", x2);

  return 0;
}

#include<stdio.h>
#include<math.h>

#define T 1.0
#define A 1.0

double dxdt ( const double x, const double t ) { return A * x; }

void solve_de(
  double (*dxdt)(const double x, const double t),
  const double interval
) {
  const int N = (int)(T / interval);
  double x = 1.0;

  for(int n = 0; n < N; n++) {
    double t = interval * n;
    double k1 = interval * dxdt(x, t);
    x += k1;
  }
  printf("result: %f\n", x);
  printf("error = %.10f\n", fabs(x - exp(T)));
}

void solve_de_heun(
  double (*dxdt)(const double x, const double t),
  const double interval
) {
  const int N = (int)(T / interval);
  double x = 1.0;

  for(int n = 0; n < N; n++) {
    double t = interval * n;
    double k1 = interval * dxdt(x, t);
    double k2 = interval * dxdt(x + k1, t + interval);
    x += (k1 + k2) / 2.0;
  }
  printf("result: %f\n", x);
  printf("error = %.10f\n", fabs(x - exp(T)));
}

void solve_de_runge_kutta(
  double (*dxdt)(const double x, const double t),
  const double interval
) {
  const int N = (int)(T / interval);
  double x = 1.0;

  for(int n = 0; n < N; n++) {
    double t = interval * n;
    double k1 = interval * dxdt(x, t);
    double k2 = interval * dxdt(x + k1 / 2.0, t + interval / 2.0);
    double k3 = interval * dxdt(x + k2 / 2.0, t + interval / 2.0);
    double k4 = interval * dxdt(x + k3, t + interval);
    x= x + (k1 + 2.0 * k2 + 2.0 * k3 + k4)/6.0;
  }
  printf("result: %f\n", x);
  printf("error = %.10f\n", fabs(x - exp(T)));
}

int main ( void )
{
  double intervals[4] = {0.1, 0.01, 0.001, 0.0001};

  printf("--- euler ---\n");
  for(int i = 0; i < 4; i++) {
    printf("h = %.5f\n", intervals[i]);
    solve_de(dxdt, intervals[i]);
  }
  printf("-----\n");

  printf("--- heun ---\n");
  for(int i = 0; i < 4; i++) {
    printf("h = %.5f\n", intervals[i]);
    solve_de_heun(dxdt, intervals[i]);
  }
  printf("-----\n");

  printf("--- runge kutta ---\n");
  for(int i = 0; i < 4; i++) {
    printf("h = %.5f\n", intervals[i]);
    solve_de_runge_kutta(dxdt, intervals[i]);
  }
  printf("-----\n");

  return 0;
}

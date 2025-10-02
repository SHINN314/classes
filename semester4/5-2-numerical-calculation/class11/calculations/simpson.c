#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define A 0.0 // 積分区間の先頭
#define B 1.0 // 積分区間の最後
#define N 100 // 分割数

double func ( double x ) { return 4.0 * sqrt ( 1 - x * x ); }

double simpson(double (*f)(double), const double a, const double b, const int n) {
    /*
        f: 被積分関数
        a: 下端
        b: 上端
        n: 分割数
    */
    double h = (b - a)/n; // 分割の幅
    double r = 0;

    for(int i = 0; i < n; i += 2) {
        r += h * ((*f)(a + i*h) + 4*(*f)(a + (i+1)*h) + (*f)(a + (i+2)*h)) / 3;
    }

    printf ( "n = %d, r = %1.10f, err = %1.10f\n", n, r, fabs ( r - M_PI ) );

    return fabs(r - M_PI);

}

void save_dat(int *x_data, double *y_data, int n) {
  FILE *fout_data = fopen("xy_data_simpson.dat", "w");

  for(int i = 0; i < n; i++) {
    int x = x_data[i];
    double y = y_data[i];
    fprintf(fout_data, "%d %lf\n", x, y);
  }
  fclose(fout_data);
}

void write_graph(char *file_name) {
  FILE *gp = popen("/usr/bin/gnuplot", "w");
  if(gp == NULL) {
    perror("popne");
    exit(1);
  }

  fprintf(gp, "plot 'xy_data_simpson.dat' with line\n");
  fprintf(gp, "set logscale\n");
  fprintf(gp, "set xtics (1, 2, 4, 8, 16, 32, 64, 128)\n");
  fprintf(gp, "set ytics (10, 1, 0, 10**-1, 10**-2, 10**-3, 10**-4, 10**-5, 10**-6, 10**-7, 10**-8)\n");
  fprintf(gp, "plot 'xy_data_simpson.dat' with lines lw 3 title 'simpson'\n");


  fprintf(gp, "set terminal pngcairo\n");
  fprintf(gp, "set out'%s'\n", file_name);
  fprintf(gp, "replot\n");

  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);
}

int main ( void )
{
  double a = A, b = B;

  int splits[7] = {2, 4, 8, 16, 32, 64, 128};
  double results[7];

  for(int i = 0; i < 7; i++) {
    results[i] = simpson(func, a, b, splits[i]);
  }

  save_dat(splits, results, 7);

  char *filename = "simpson.png";
  write_graph(filename);

  return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define T 100.0
#define h 0.01
#define K 1.0

double dxdt ( const double x, const double v, const double t ) { return v; }
double dvdt ( const double x, const double v, const double t ) { return ( - K ) * x ; }

void solve_second_de(
  const double (*dxdt)(const double x, const double v, const double t),
  const double (*dvdt)(const double x, const double v, const double t),
  const double interval,
  const char *file_name
) {
  // 変数の定義
  const int N = (int)(T / interval);
  double x = 1.0, v = 0.0;

  // gnuplotの起動
  FILE *gp = popen("/usr/bin/gnuplot", "w");
  if(gp == NULL) {
    perror("popen");
    exit(1);
  }

  // datファイルを開く
  FILE *fp = fopen("pendulum.dat", "w");
  if(fp == NULL) {
    perror("fopen");
    exit(1);
  }

  for(int n = 0; n < N+1; n++) {
    double t = n * interval;
    fprintf(fp, "%f %f %f\n", t, x, v);
    double k1x = interval * dxdt(x, v, t);
    double k1v = interval * dvdt(x, v, t);
    x += k1x;
    v += k1v;
  }

  // グラフの描画
  fprintf(gp, "plot 'pendulum.dat' using 1:3 with line\n");

  // pngファイルに出力
  fprintf(gp, "set terminal png\n");
  fprintf(gp, "set out '%s'\n", file_name);
  fprintf(gp, "replot\n");

  // メモリの解法
  fprintf(gp, "exit\n");
  fflush(gp);
  pclose(gp);
  fclose(fp);
}

int main ( void )
{
  char *file_names[4] = {
    "../report/pictures/pendulum1.png",
    "../report/pictures/pendulum2.png",
    "../report/pictures/pendulum3.png",
    "../report/pictures/pendulum4.png"
  };
  double intervals[4] = {0.1, 0.01, 0.001, 0.0001};

  // solve_second_de(dxdt, dvdt, intervals[3], file_names[3]);

  for(int i = 0; i < 4; i++) {
    solve_second_de(dxdt, dvdt, intervals[i], file_names[i]);
  }

  return 0;
}

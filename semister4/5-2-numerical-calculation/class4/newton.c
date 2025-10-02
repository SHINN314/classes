#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 円周率の定義
#define PI 3.141592653589793238462643

// 最小誤差の定義
#define Epsilon ( 1e-14 )

// ニュートン法
double newton_method ( double ( *f ) ( double ), double ( *dfdx ) ( double ), double initial_value, double epsilon, double t_value )
{
  double x = initial_value;

  int i = 0;
  printf("繰り返し回数 解 絶対誤差 相対誤差\n");
  while ( fabs ( f ( x ) ) > epsilon ) {
    // 解の値を出力
    fprintf ( stderr, "%d & %1.16f ", i, x );
    // 絶対誤差を計算する
    double error = fabs(x - t_value);
    fprintf(stderr, "& %1.16f ", error);
    // 相対誤差を計算する
    double relative_error = fabs(x - t_value) / t_value;
    fprintf(stderr, "& %1.16f\n", relative_error);


    // newton法による解の更新
    x = x - f ( x ) / dfdx ( x );
    i++;
  }

  return x;
}

// 課題3
void practice3() {
  // fの定義
  double f ( double x ) { return sin(x); } // solutions is 0
  // dfdxの定義
  double dfdx ( double x ) { return cos(x); }

  // initial_value = 3.0
  double x = newton_method ( f, dfdx, 3.0, Epsilon, PI );
  printf ( "answer = %1.16f\n", x );

  printf("\n");

  // initial_value = 1.6 -> こうすると面白い結果を得る(dfdxの値が0に近いからかな？傾きが0に近くないところをスタート地点とする必要がありそう)
  x = newton_method ( f, dfdx, 1.6, Epsilon, PI );
  printf ( "answer = %1.16f\n", x );

  printf("\n");

  // initial_value = 2.0
  x = newton_method(f, dfdx, 2.0, Epsilon, PI);
  printf("answer = %1.16f\n", x);
}

// 課題4、課題5
void practice4() {
  // f_1、f_2の定義
  double f_1(double x) {
    return x*x - 2*x + 1;
  }

  double f_2(double x) {
    return x*x - 3*x + 2;
  }

  // dfdx_1、dfdx_2の定義
  double dfdx_1(double x) {
    return 2*x - 2;
  }

  double dfdx_2(double x) {
    return 2*x - 3;
  }

  // f_1でnewton法を適用
  double x = newton_method(f_1, dfdx_1, 1.1, Epsilon, 1);
  printf("answer = %1.16f\n", x);

  printf("\n");

  // f_2でnewton法を適用
  x = newton_method(f_2, dfdx_2, 1.1, Epsilon, 1);
  printf("answer = %1.16f\n", x);

  // f_1のほうがステップ数が多い。やっぱりdfdxが0に近いことが原因なのだろうか...?

}

// 課題6
// z^2 + 1 = 0 の解を求めるための多変数newton法
void mult_newton(double *initial_array) {
  // 実部と虚部を取得
  double x = initial_array[0];
  double y = initial_array[1];

  // カウンタの定義
  int i = 0;

  // z*z + 1 の実部と虚部が両方ともEpsilonより大きいときにnewton法で値を更新
  while(fabs(x*x - y*y + 1) > Epsilon && fabs(2*x*y) > Epsilon) {
    // 値の出力
    printf("%d: x=%1.16f y=%1.16f\n", i, x, y);

    // 値の更新
    x = x - (x*x*x - x*y*y + x + 2*x*y*y) / 2*(x*x + y*y);
    y = y - (-x*x*y - 2*x*y*y + y*y*y - y) / 2*(x*x + y*y);
    i++;
  }

  initial_array[0] = x;
  initial_array[1] = y;
}

void practice6() {
  double initial_array[2] = {0.1, 1.1};
  mult_newton(initial_array);
  printf("answer: x=%1.16f y=%1.16f\n", initial_array[0], initial_array[1]);
}


int main ( void )
{
  practice3();
  // practice4();
  //  practice6();
  return 0;
}

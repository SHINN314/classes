#include <stdio.h>
#include <math.h>

// 正弦関数を返す
double f ( double x ) { return sin ( x ); }

int main ( void )
{
  double x = M_PI / 4.0;
  double h = 1.0;

  // 中心差分で微分係数を近似する
  // hを1/10しながら微分係数とその相対誤差を求めていく
  while(h >= 1.0e-14) {
    double dfdx = ( f ( x + h / 2.0 ) - f ( x - h / 2.0 ) ) / h;
    double relerr = fabs ( dfdx - cos ( x ) ) / fabs ( cos ( x ) );
    printf ( "%1.14f %1.14f %1.14f\n", h, dfdx, relerr );
    h = h / 10;
  }

}

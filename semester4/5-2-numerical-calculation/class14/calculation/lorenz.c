#include <stdio.h>

#define T 100.0
#define h 0.01
#define A 10.0
#define B 28.0
#define C ( 8.0 / 3.0 )

double dxdt ( const double x, const double y, const double z, const double t ) { return A * ( y - x ); }
double dydt ( const double x, const double y, const double z, const double t ) { return x * ( B - z ) - y; }
double dzdt ( const double x, const double y, const double z, const double t ) { return x * y - C * z; }

int main ( void )
{
  const int N = ( int ) ( T / h );
  double x = 0.5, y = 0.5, z = 0.5;

  for ( int n = 0; n < N + 1; n++ ) {
    double t = h * n;
    printf ( "%f %f %f %f\n", t, x, y, z);
    double k1_x = dxdt ( x, y, z, t );
    double k1_y = dydt ( x, y, z, t );
    double k1_z = dzdt ( x, y, z, t );
    x += h * k1_x;
    y += h * k1_y;
    z += h * k1_z;
  }
}

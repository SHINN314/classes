#include <stdio.h>
#include <string.h>

#define DOUBLE_BITS ( 64 )

// xのi番目のビットを取得する
// 最大ビット数は63
int bit ( const double x, const int i )
{
  unsigned long v;
  memcpy ( &v, &x, sizeof ( double ) );
  return  ( v >> i ) & 1;
}

int main ( void )
{
  double x = 314;

  // IEEE754企画でdouble xを確認
  for ( int i = DOUBLE_BITS - 1; i >= 0; i-- ) {
    int b = bit ( x, i );
    // xのi番目のビットを出力する
    // 符号と仮数、指数の部分を分けるように出力する
    printf ( "%d%s", b, ( i == 63 || i == 52 ) ? " " : "" );
  }
  printf ( "\n" );
}

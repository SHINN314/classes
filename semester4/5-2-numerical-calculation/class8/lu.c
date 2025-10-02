#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N ( 3 )
#define Eps ( 1e-8 )

// 行列の出力
void printMatrix ( const int n, double M [ n ] [ n ] )
{
  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < n; j++ ) {
      printf ( "%c%2.2f%s", ( M [ i ] [ j ] < 0 ) ? '-' : ' ', fabs ( M [ i ] [ j ] ), ( j == n - 1 ) ? "\n" : " " );
    }
  }
  printf ( "--\n" );
}

// 列ベクトルの表示
void printVector ( const int n, double v [ n ] )
{
  for ( int i = 0; i < n; i++ ) {
    printf ( "%c%2.2f\n", ( v [ i ] < 0 ) ? '-' : ' ', fabs ( v [ i ] ) );
  }
  printf ( "--\n" );
}

// LU分解の判定
void checkLU (const int n, double A [ n ] [ n ],
	      double L [ n ] [ n ], double U [ n ] [ n ] )
{
  // Print L
  printf ( "L:\n" );
  printMatrix ( n, L );
  // Print U#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N ( 3 )
#define Eps ( 1e-8 )

// 行列の出力
void printMatrix ( const int n, double M [ n ] [ n ] )
{
  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < n; j++ ) {
      printf ( "%c%2.2f%s", ( M [ i ] [ j ] < 0 ) ? '-' : ' ', fabs ( M [ i ] [ j ] ), ( j == n - 1 ) ? "\n" : " " );
    }
  }
  printf ( "--\n" );
}

// 列ベクトルの表示
void printVector ( const int n, double v [ n ] )
{
  for ( int i = 0; i < n; i++ ) {
    printf ( "%c%2.2f\n", ( v [ i ] < 0 ) ? '-' : ' ', fabs ( v [ i ] ) );
  }
  printf ( "--\n" );
}

  printf ( "U:\n" );
  printMatrix ( n, U );
  // Check LU = A
  int correct = 1;
  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < n; j++ ) {
      double r = 0.0;
      for ( int k = 0; k < n; k++ ) {
	r += L [ i ] [ k ] * U [ k ] [ j ];
      }
      if ( fabs ( r - A [ i ] [ j ] ) > Eps ) { correct = 0; }
    }
  }
  printf ( "%s: %s\n", __func__, correct ? "Good" : "Bad" );
}

// ベクトルxが連立方程式の解か調べる
void checkAnswer ( const int n, double A [ n ] [ n ], double x [ n ], double b [ n ] )
{
  // Check Ax = b
  int correct = 1;
  for ( int i = 0; i < n; i++ ) {
    double r = 0.0;
    for ( int j = 0; j < n; j++ ) {
      r += A [ i ] [ j ] * x [ j ];
    }
    if ( fabs ( r - b [ i ] ) > Eps ) { correct = 0; }
  }
  printf ( "%s: %s\n", __func__, correct ? "Good" : "Bad" );
}

// LU分解を行う関数
void LUDecomposition ( const int n, double A [ n ] [ n ], double L [ n ] [ n ], double U [ n ] [ n ], double r [ n ] )
{
  // Copy A to tmp to preserve A
  double tmp [ n ] [ n ];
  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < n; j++ ) {
      tmp [ i ] [ j ] = A [ i ] [ j ];
    }
  }

  // Prepare r for pivoting
  for ( int i = 0; i < n; i++ ) {
    r [ i ] = i;
  }

  //
  // Write the code for LU decomposition here
  //
  for(int i = 0; i < n; i++) {
    // ピボット選択
    double pivot = tmp[i][i];
    int pivot_row = i;  

    for(int j = i; j < n; j++) {
      if(abs(pivot) < abs(tmp[j][i])) {
        pivot = tmp[j][i];
        pivot_row = j;
      }
    }

    // 入れ替えの記録
    double memo_row = r[i];
    r[i] = r[pivot_row];
    r[pivot_row] = memo_row;

    // tmpの行の入れ替え
    for(int j = 0; j < n; j++) {
      double memo_content = tmp[i][j];
      tmp[i][j] = tmp[pivot_row][j];
      tmp[pivot_row][j] = memo_content;
    }

    // 行列Aの行の入れ替え
    for(int j = 0; j < n; j++) {
      double memo_content = A[i][j];
      A[i][j] = A[pivot_row][j];
      A[pivot_row][j] = memo_content;
    }

    // 行列Uに値を代入
    for(int j = 0; j < i; j++) {
      // 下三角には0を代入
      U[i][j] = 0;
    }

    for(int j = i; j < n; j++) {
      U[i][j] = tmp[i][j];
    }

    // tmpの行列を更新
    double diagonal_component = tmp[i][i]; // 対角成分の値をメモ

    for(int j = i; j < n; j++) {
      tmp[j][i] = tmp[j][i]/diagonal_component;
    }

    for(int j = i+1; j < n; j++) {
      for(int k = i+1; k < n; k++) {
        tmp[j][k] = tmp[j][k] - tmp[i][k]*tmp[j][i];
      }
    }

    // 行列Lに値を代入
    for(int j = 0; j < i; j++) {
      // 上三角には0を代入
      L[j][i] = 0;
    }

    for(int j = i; j < n; j++) {
      L[j][i] = tmp[j][i];
    }
  }

}

// 前進代入
void forwardSubstitution ( const int n, double L [ n ] [ n ],
			   double y [ n ], double b [ n ], double r [ n ] )
{
  for ( int i = 0; i < n; i++ ) {
    double r = b [ i ];
    for ( int j = 0; j < i; j++ ) {
      r -= L [ i ] [ j ] * y [ j ];
    }
    y [ i ] = r;
  }
}

// 後進代入
void backwardSubstitution ( const int n, double U [ n ] [ n ],
			    double x [ n ], double y [ n ] )
{
  for ( int i = n - 1; i >= 0; i-- ) {
    double r = y [ i ];
    for ( int j = n - 1; j > i; j-- ) {
      r -= U [ i ] [ j ] * x [ j ];
    }
    x [ i ] = r / U [ i ] [ i ];
  }
}

int main ( void )
{
  double A [ N ] [ N ] = { { 1, 2, 3 }, { 2, 4, 4 }, { 3, 1, 2 } };
  double b [ N ] = { 6, 10, 6 };
  double L [ N ] [ N ], U [ N ] [ N ]; // LU分解したときの行列を保存するための2次元配列
  double x [ N ], y [ N ], r [ N ];

  LUDecomposition ( N, A, L, U, r );
  checkLU ( N, A, L, U );

  forwardSubstitution ( N, L, y, b, r );
  backwardSubstitution ( N, U, x, y );
  checkAnswer ( N, A, x, b );
}

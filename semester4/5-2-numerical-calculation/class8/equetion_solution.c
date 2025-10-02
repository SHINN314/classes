#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define N ( 3 )
#define Eps ( 1e-8 )

// 反復回数
int repetition = 100;


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

// ベクトルの収束を定義
int is_convergence(const int n, double v[n], const double epsilon) {
    for(int i = 0; i < n; i++) {
        if(fabs(v[i]) > epsilon) {
            printf("not converted\n");
            return 0;
        }
    }

    printf("converted\n");
    return 1;
}

// ヤコビ法による解法
void jacob(const int n, double A[n][n], double b[n], double x[n]) {
    double delta_vector[n]; // 左辺と右辺の差のベクトル
    double delta_content = 0; // delta_vectorを求めるときに使う変数
    double x_new[n]; // 更新後のxベクトル

    for(int p = 0; p < repetition; p++) {
        for(int i = 0; i < n; i++) {
            // x_newベクトルの計算
            double sum = 0;
            for(int j = 0; j < n; j++) {
                if(j != i) {
                   sum += A[i][j]*x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // 解の更新
        for(int j = 0; j < n; j++) {
            x[j] = x_new[j];
        }
    }
}

// ガウス・ザイデル法による解法
void gs(const int n, double A[n][n], double b[n], double x[n]) {
    double delta_vector[n]; // 左辺と右辺の差のベクトル
    double delta_content = 0; // delta_vectorを求めるときに使う変数
    double x_new[n]; // 更新後のxベクトル

    for(int i = 0; i < n; i++) {
        // x_newの初期化
        x_new[i] = x[i];
    }

    for(int p = 0; p < repetition; p++) {
        for(int i = 0; i < n; i++) {
            // x_newベクトルの計算
            double sum = 0;
            for(int j = 0; j < n; j++) {
                if(j != i) {
                   sum += A[i][j]*x_new[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // 解の更新
        for(int j = 0; j < n; j++) {
            x[j] = x_new[j];
        }
    }
}

// SOR法による解法
void sor(const int n, double A[n][n], double b[n], double x[n]) {
    double delta_vector[n]; // 左辺と右辺の差のベクトル
    double delta_content = 0; // delta_vectorを求めるときに使う変数
    double x_new[n]; // 更新後のxベクトル
    double w = 1.5; // 加速パラメータ

    for(int i = 0; i < n; i++) {
        // x_newの初期化
        x_new[i] = x[i];
    }

    for(int p = 0; p < repetition; p++) {
        for(int i = 0; i < n; i++) {
            // x_newベクトルの計算
            double sum = 0;
            for(int j = 0; j < n; j++) {
                if(j != i) {
                   sum += A[i][j]*x_new[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        // 解の更新
        for(int i = 0; i < n; i++) {
            x[i] = w*x_new[i] + (1 - w)*x[i];

            // x_newの更新
            x_new[i] = x[i];
        }
    }
}

int main() {
    double A [ N ] [ N ] = { { 3, 2, 1 }, { 1, 3, -2 }, { 2, -1, 4 } };
    double b [ N ] = { 4, 6, -3 };
    double x[N] = {0, 0};
    int repetitions[5] = {20, 40, 60, 80, 1000};

    printf("first x vector\n");
    printVector(N, x);

    // ヤコビ法による解の導出
    for(int i = 0; i < 5; i++) {
        printf("jacob: repetition=%d\n", repetitions[i]);
        repetition = repetitions[i];
        jacob(N, A, b, x);
        printVector(N, x);
        is_convergence(N, x, Eps);
    }


    // ガウス・ザイデル法による解の導出
    for(int i = 0; i < 5; i++) {
        printf("jacob: repetition=%d\n", repetitions[i]);
        repetition = repetitions[i];
        gs(N, A, b, x);
        printVector(N, x);
        is_convergence(N, x, Eps);
    }

    // SOR法による解の導出
    for(int i = 0; i < 5; i++) {
        printf("jacob: repetition=%d\n", repetitions[i]);
        repetition = repetitions[i];
        sor(N, A, b, x);
        printVector(N, x);
        is_convergence(N, x, Eps);
    }

    return 0;
}


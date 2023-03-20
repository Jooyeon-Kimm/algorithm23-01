/*
Input: 
2
2 3
4 1
5 7
6 8

Output:
28 38
26 36
*/
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;

void matrixmult(int n, matrix_t A, matrix_t B, matrix_t& C) {

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                C[i][j] += A[i][k] * B[k][j];
             
}

void matrixread(int n, matrix_t& M) {
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            scanf("%d", &M[i][k]);
}

int main() {
    int n;
    scanf("%d", &n);

    matrix_t A(n + 1, vector<int>(n + 1));
    matrixread(n, A);

    matrix_t B(n + 1, vector<int>(n + 1));
    matrixread(n, B);

    matrix_t C(n + 1, vector<int>(n + 1));
    matrixmult(n, A, B, C);

    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            if (k < n)
                printf("%d ", C[i][k]);
            else
                printf("%d\n", C[i][k]);
}
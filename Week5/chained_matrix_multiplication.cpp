#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef vector<int> v1;
typedef vector<v1> v2;
#define INF 999999

/*
연쇄 행렬 곱셈 : 동적 계획 (Dynamic Programming)

1단계: 재귀 관계식을 찾는다.
M: 연쇄 행렬을 곱하는데 필요한 곱셈의 최소 회수 행행렬을
M[i][j]: Ai에서 Aj까지 행렬을 곱한느데 필요한 곱셈의 최소 회회수

For 1 <= i <= k <= n,
if i == k , M[i][k] = 0
if i < k , M[i][k] = z: 1~k-1, min(M[i][k] + M[z+1][k] + di-1 * dz * dk)

2단계: 상향식 방법으로 해답을 구한다.
- 초기화: M[i][i] = 0 (주 대각선을 0으로)
- 최종 목표: M[1][n]
- 상향식 계산: 대각선 1번, 대각선 2번, ..., 대각선 n-1 번ㅇ
*/

int minimum(int i, int j, int& mink, v1& d, v2& M) {
    int minValue = INF, value;
    for (int k = i; k <= j - 1; k++) {
        value = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];

        if (minValue > value) {
            minValue = value;
            mink = k;
        }

    }
    return minValue;
}


void minMult(int n, v1& D, v2& P, v2& M) {
    int i, k, z, diagonal;

    // 주 대각선을 0으로 초기화
    for (i = 1; i <= n; i++) {
        M[i][i] = 0;
        P[i][i] = 0;
    }

    for (diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (i = 1; i <= n - diagonal; i++) {
            k = i + diagonal;

            //  M[i][k] = min(M[i][z] + M[z+1][k] + d[i-1]*d[z]*d[k]);
            M[i][k] = minimum(i, k, z, D, M);
            P[i][k] = z;

        }
    }
}


// Print Optimal Order
void printPath(v2& P, int i, int j) {

    cout << "(";
    if (i == j) {
        cout << "A" << i << ")";
        return;
    }

    int k = P[i][j];
    printPath(P, i, k);
    printPath(P, k + 1, j);
    cout << ")";
}



void printMatrix(v2& arr, int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            if (arr[i][j] == INF) {
                continue;
            }

            cout << arr[i][j];

            if (j == n) {
                cout << "\n";
            }
            else {
                cout << " ";
            }
        }
    }
}

int main(void) {
    // 행렬의 개수 n
    int n;
    cin >> n;


    v1 D(n + 1); // 행렬의 크기 값의 배열 D (배열의 크기는 n+1)
    v2 M(n + 1, v1(n + 1, INF)); // M[i][k] == 행렬 i에서 k까지 연쇄 곱셈의 최솟값
    v2 P(n + 1, v1(n + 1, INF)); //

    for (int i = 0; i < n + 1; i++) {
        cin >> D[i];
    }


    minMult(n, D, P, M);

    // cout << endl << "Matrix M" << endl;
    printMatrix(M, n);

    // cout << endl << "Matrix P" << endl;
    printMatrix(P, n);

    cout << M[1][n] << endl;

    printPath(P, 1, n);

}
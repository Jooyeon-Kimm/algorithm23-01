#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef vector<int> v1;
typedef vector<v1> v2;
#define INF 999999

/*
���� ��� ���� : ���� ��ȹ (Dynamic Programming)

1�ܰ�: ��� ������� ã�´�.
M: ���� ����� ���ϴµ� �ʿ��� ������ �ּ� ȸ�� �������
M[i][j]: Ai���� Aj���� ����� ���Ѵ��� �ʿ��� ������ �ּ� ȸȸ��

For 1 <= i <= k <= n,
if i == k , M[i][k] = 0
if i < k , M[i][k] = z: 1~k-1, min(M[i][k] + M[z+1][k] + di-1 * dz * dk)

2�ܰ�: ����� ������� �ش��� ���Ѵ�.
- �ʱ�ȭ: M[i][i] = 0 (�� �밢���� 0����)
- ���� ��ǥ: M[1][n]
- ����� ���: �밢�� 1��, �밢�� 2��, ..., �밢�� n-1 ����
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

    // �� �밢���� 0���� �ʱ�ȭ
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
    // ����� ���� n
    int n;
    cin >> n;


    v1 D(n + 1); // ����� ũ�� ���� �迭 D (�迭�� ũ��� n+1)
    v2 M(n + 1, v1(n + 1, INF)); // M[i][k] == ��� i���� k���� ���� ������ �ּڰ�
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
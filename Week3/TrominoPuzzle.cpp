#include <iostream>
#include <vector>
using namespace std;

int order = 0;
typedef vector<vector<int> > v2;
typedef vector<int> v1;
typedef struct { int x; int y; } pos;
typedef vector<pos> vPos;

void divide(int n, v2& A, v2& A11, v2& A12, v2& A21, v2& A22) {
    int m = n / 2;
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < m; k++) {
            A11[i][k] = A[i][k];
            A12[i][k] = A[i][k + m];
            A21[i][k] = A[i + m][k];
            A22[i][k] = A[i + m][k + m];
        }
    }
}

void combine(int n, v2& A, v2& A11, v2& A12, v2& A21, v2& A22) {
    int m = n / 2;
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < m; k++) {
            A[i][k] = A11[i][k];
            A[i][k + m] = A12[i][k];
            A[i + m][k] = A21[i][k];
            A[i + m][k + m] = A22[i][k];
        }
    }
}

int getArea(int n, int sy, int sx, int y, int x) {
    int area = 1;
    int m = n / 2;
    if (x >= sx + m) area += 1;
    if (y >= sy + m) area += 2;
    return area;
}

void printVector(int n, v2& v) {
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            cout << v[k][j];

            // 마지막 원소이면 줄 바꾸기
            if (j == n - 1) cout << endl;
            else cout << " ";
        }
    }
}

void fillCenter(int n, int area, int sy, int sx, v2& V, vPos& fillPos) {

    int m = n / 2;
    order += 1;
    if (area != 1) {
        V[m - 1][m - 1] = order;
        fillPos[0].x = sx + m - 1;
        fillPos[0].y = sy + m - 1;
    }
    if (area != 2) {
        V[m - 1][m] = order;
        fillPos[1].x = sx + m;
        fillPos[1].y = sy + m - 1;
    }
    if (area != 3) {
        V[m][m - 1] = order;
        fillPos[2].x = sx + m - 1;
        fillPos[2].y = sy + m;
    }
    if (area != 4) {
        V[m][m] = order;
        fillPos[3].x = sx + m;
        fillPos[3].y = sy + m;
    }
}


void tromino(int n, int sy, int sx, int y, int x, v2& V) {
     
    // n이 1이면 채울 필요 X
    if (n == 1) return;

    // n이 2이면 나누지 않고 바로 채운다.
    int area = getArea(n, sy, sx, y, x);            // 점이 어느 사분면에 있는지?
    
    pos p; 
    p.x = x; 
    p.y = y;

    vPos fillPos(4, p);
    fillCenter(n, area, sy, sx, V, fillPos);         // 점이 있는 사분면을 제외한곳을 색칠
    if (n == 2) return;

    // n이 4이상이면 4개로 나눈다.
    int m = n / 2;
    v2 V11(m, v1(m, 0));
    v2 V12(m, v1(m, 0));
    v2 V21(m, v1(m, 0));
    v2 V22(m, v1(m, 0));
    divide(n, V, V11, V12, V21, V22);

    // 각 벡터에 대해 트로미노
    tromino(m, sy, sx, fillPos[0].y, fillPos[0].x, V11);
    tromino(m, sy, sx + m, fillPos[1].y, fillPos[1].x, V12);
    tromino(m, sy + m, sx, fillPos[2].y, fillPos[2].x, V21);
    tromino(m, sy + m, sx + m, fillPos[3].y, fillPos[3].x, V22);

    // 병합
    combine(n, V, V11, V12, V21, V22);
}


int main() {

    int n, row, col;
    cin >> n >> row >> col;

    v2 V(n, v1(n, 0));
    tromino(n, 0, 0, row, col, V);
    printVector(n, V);

    return 0;
}
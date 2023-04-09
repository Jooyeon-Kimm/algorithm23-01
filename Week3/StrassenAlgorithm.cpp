/* https://www.youtube.com/watch?v=Q3YQeYXPkXE */

#include <iostream>
#include <vector>
using namespace std;

int cnt = 0;
int threshold;
typedef vector<vector<int> > matrix;
typedef vector<int> mat;

void input_matrix(matrix& M, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            cin >> M[i][k];
        }
    }
}

void print_matrix(int n, matrix& M) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            cout << M[i][k];

            // 마지막 원소이면 줄 바꾸기
            if (k == n - 1) printf("\n");
            else printf(" ");
        }
    }
}


void madd(int n, matrix& A, matrix& B, matrix& C) {
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            C[i][k] = A[i][k] + B[i][k];
}

void msub(int n, matrix& A, matrix& B, matrix& C) {
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            C[i][k] = A[i][k] - B[i][k];
}

void mmult(int n, matrix& A, matrix& B, matrix& C) {
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            for (int z = 0; z < n; z++)
                C[i][k] += A[i][z] * B[z][k];
}

void partition(int m, matrix& M, matrix& M11, matrix& M12, matrix& M21, matrix& M22) {
    for (int i = 0; i < m; i++) {
        for (int k = 0; k < m; k++) {
            M11[i][k] = M[i][k];
            M12[i][k] = M[i][k + m];
            M21[i][k] = M[i + m][k];
            M22[i][k] = M[i + m][k + m];
        }
    }
}

// partition 반대로
void combine(int n, matrix& A, matrix& A11, matrix& A12, matrix& A21, matrix& A22) {

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


void strassen(int n, matrix& A, matrix& B, matrix& C) {
    cnt++; // strassen() 호출 횟수 세기

    if (n <= threshold) {
        mmult(n, A, B, C);
    }
    else {
        int m = n / 2;
        
        // A, B를 submatrix 4개로 각각 나누기
        matrix A11(m, mat(m, 0)), A12(m, mat(m, 0)), A21(m, mat(m, 0)), A22(m, mat(m, 0));
        matrix B11(m, mat(m, 0)), B12(m, mat(m, 0)), B21(m, mat(m, 0)), B22(m, mat(m, 0));
        matrix C11(m, mat(m, 0)), C12(m, mat(m, 0)), C21(m, mat(m, 0)), C22(m, mat(m, 0));
        partition(m, A, A11, A12, A21, A22);
        partition(m, B, B11, B12, B21, B22);

        //2. M1부터 M7까지 계산
        matrix M1(m, mat(m, 0)), M2(m, mat(m, 0)), M3(m, mat(m, 0)), M4(m, mat(m, 0));
        matrix M5(m, mat(m, 0)), M6(m, mat(m, 0)), M7(m, mat(m, 0));
        matrix L(m, mat(m, 0)), R(m, mat(m, 0));

        //M1
        madd(m, A11, A22, L);
        madd(m, B11, B22, R);
        strassen(m, L, R, M1);

        //M2
        madd(m, A21, A22, L);
        strassen(m, L, B11, M2);

        //M3
        msub(m, B12, B22, L);
        strassen(m, A11, L, M3);

        //M4
        msub(m, B21, B11, L);
        strassen(m, A22, L, M4);

        //M5
        madd(m, A11, A12, L);
        strassen(m, L, B22, M5);

        //M6
        msub(m, A21, A11, L);
        madd(m, B11, B12, R);
        strassen(m, L, R, M6);

        //M7
        msub(m, A12, A22, L);
        madd(m, B21, B22, R);
        strassen(m, L, R, M7);

        //3. make C with M1 ~ M7 -> you might need add, sub
        //C11
        madd(m, M1, M4, L);
        msub(m, L, M5, R);
        madd(m, R, M7, C11);

        //C12
        madd(m, M3, M5, C12);

        //C21
        madd(m, M2, M4, C21);

        //C22
        madd(m, M1, M3, L);
        msub(m, L, M2, R);
        madd(m, R, M6, C22);


        //4. combine C11 ~ C22 into the only C 
        combine(n, C, C11, C12, C21, C22);
    }
}



int resize(int n) {
    int k = 1;
    while (k < n) k *= 2;
    return k;
}


int main() {

    int k, n;
    cin >> n >> threshold;
    k = resize(n);

    matrix A(k, mat(k, 0)), B(k, mat(k, 0)), C(k, mat(k, 0));

    input_matrix(A, n);
    input_matrix(B, n);

    strassen(k, A, B, C);

    cout << cnt << "\n";
    print_matrix(n, C);

    return 0;
}
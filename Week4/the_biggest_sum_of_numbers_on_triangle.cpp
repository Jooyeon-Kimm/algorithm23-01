#include <iostream>
#include <vector>
#include <algorithm>
#define MIN -10001

using namespace std;
typedef vector<int> v1;
typedef vector<vector<int>> v2;

// �ִ������ ã�� (dynamic programming)
void findMax(int n, v2& dp, v2& triangle, v2& path) {
    // �� �� ù ���� �ʱ�ȭ
    dp[0][0] = triangle[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j]; // dp �ʱ�ȭ

            if (j != 0 && dp[i][j] < dp[i][j] + dp[i - 1][j - 1]) {
                dp[i][j] += dp[i - 1][j - 1];
                path[i][j] = 1;
            }
            if (dp[i][j] <= triangle[i][j] + dp[i - 1][j]) {
                dp[i][j] = triangle[i][j] + dp[i - 1][j];
                path[i][j] = 0;
            }
        }
    }
}

// ���������� ġ��ģ �ִ� �ﰢ�� ���� ��� ���
// �� �Ʒ� �ִ���Һ��� �����ؼ�
// ���� ������ path�� 1�̸�, ���� �� ���ҷ� �̵�
// ���� ������ path�� 0�̸�, ���� ���ҷ� �̵�
void printPath(v2& triangle, v2& path, int x, int y, int n) {
    // �������� ���ٰ�
    // ������ �ε����� ������ �����, ����
    if (x == -1) {
        return;
    }

    if (path[x][y] == 1) {
        printPath(triangle, path, x - 1, y - 1, n);
    }
    else {
        printPath(triangle, path, x - 1, y, n);
    }
    cout << triangle[x][y];
    if (x != n - 1) cout << " ";
}

// 2d ���� ����Լ�
void print2D(v2 arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= i; k++) {
            cout << arr[i][k];
            if (k == i) cout << endl;
            else cout << " ";
        }
    }
}

// �����Լ�
int main() {
    // �Ľ�Į �ﰢ���� ���� n
    int n;
    cin >> n;

    v2 path(n, v1(n, 0));       // ��� path
    v2 dp(n, v1(n, 0));         // �����ִ��� dp
    v2 triangle(n, v1(n, 0));   // ���� �Ľ�Į �ﰢ�� triangle

    // �Ľ�Į �ﰢ�� �Է¹ޱ�
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }

    // dp ä���
    findMax(n, dp, triangle, path);

    
    //// dp ����غ���
    //cout << "dp" << endl;
    //print2D(dp, n);

    //// path ����غ���
    //cout << "path" << endl;
    //print2D(path, n);
    

    // dp ������ �ٿ��� �ִ��� �ε��� ã�Ƽ�
    // max�� ���
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] >= dp[n - 1][max]) {
            max = i;
        }
    }
    cout << dp[n - 1][max] << endl;

    // ��� ���
    printPath(triangle, path, n-1, max, n);

    return 0;
}
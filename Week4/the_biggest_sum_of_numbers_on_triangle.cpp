#include <iostream>
#include <vector>
#include <algorithm>
#define MIN -10001

using namespace std;
typedef vector<int> v1;
typedef vector<vector<int>> v2;

// 최대원소합 찾기 (dynamic programming)
void findMax(int n, v2& dp, v2& triangle, v2& path) {
    // 맨 위 첫 원소 초기화
    dp[0][0] = triangle[0][0];

    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = triangle[i][j]; // dp 초기화

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

// 오른쪽으로 치우친 최대 삼각형 원소 경로 출력
// 맨 아래 최대원소부터 시작해서
// 현재 원소의 path가 1이면, 왼쪽 위 원소로 이동
// 현재 원소의 path가 0이면, 왼쪽 원소로 이동
void printPath(v2& triangle, v2& path, int x, int y, int n) {
    // 왼쪽으로 가다가
    // 벡터의 인덱스가 범위를 벗어나면, 종료
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

// 2d 벡터 출력함수
void print2D(v2 arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= i; k++) {
            cout << arr[i][k];
            if (k == i) cout << endl;
            else cout << " ";
        }
    }
}

// 메인함수
int main() {
    // 파스칼 삼각형의 높이 n
    int n;
    cin >> n;

    v2 path(n, v1(n, 0));       // 경로 path
    v2 dp(n, v1(n, 0));         // 누적최대합 dp
    v2 triangle(n, v1(n, 0));   // 원래 파스칼 삼각형 triangle

    // 파스칼 삼각형 입력받기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> triangle[i][j];
        }
    }

    // dp 채우기
    findMax(n, dp, triangle, path);

    
    //// dp 출력해보기
    //cout << "dp" << endl;
    //print2D(dp, n);

    //// path 출력해보기
    //cout << "path" << endl;
    //print2D(path, n);
    

    // dp 마지막 줄에서 최댓값의 인덱스 찾아서
    // max값 출력
    int max = 0;
    for (int i = 1; i < n; i++) {
        if (dp[n - 1][i] >= dp[n - 1][max]) {
            max = i;
        }
    }
    cout << dp[n - 1][max] << endl;

    // 경로 출력
    printPath(triangle, path, n-1, max, n);

    return 0;
}
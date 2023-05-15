#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
int num_solutions = 0;
vector<int> col;
string max_val = "0";

bool promising(int i) {
    for (int k = 1; k < i; k++) {
        if (col[k] == col[i] || abs(col[k] - col[i]) == i - k) {
            return false;
        }
    }
    return true;
}

void queens(int i) {
    if (promising(i)) {
        if (i == n) {
            num_solutions++;
            string curr_val = "";
            for (int k = 1; k <= n; k++) {
                curr_val += to_string(col[k]);
            }
            if (curr_val > max_val) {
                max_val = curr_val;
            }
        }
        else {
            for (int k = 1; k <= n; k++) {
                col[i + 1] = k;
                queens(i + 1);
            }
        }
    }
}

int main() {
    cin >> n;
    col.resize(n + 1);

    queens(0);

    cout << num_solutions << endl;
    cout << max_val;

    return 0;
}

/*
n-Queens 문제
Description

교재와 강의자료를 참고하여n-Queens 문제를 해결하는Algorithm 5.1을 완성하시오.



n의 값이 주어질 때, n-Queens 문제를 해결하는 보드의 배치가 총 몇 개인지를 카운트하고,

col 배열의 값을 숫자의 문자열로 취급했을 때 가장 큰 값을 출력하도록 수정하시오.

예)

n = 4일 때 가능한 보드의 배치는 다음과 같이 총 2개가 있다.

col1 = [2, 4, 1, 3]

col2 = [3, 1, 4, 2]

위 배치의 col 배열을 숫자의 문자열로 취급하면 각각 2413, 3142의 값을 갖는다.

따라서 이 문제의 출력은 다음과 같다.

2 ; 가능한 보드 배치의 갯수

3142 ; 가능한 보드 배치 중에서 숫자의 문자열이 가장 큰 값


Input
첫 줄에 n의 값이 주어진다.

단, n은 4보다 크거나 같다.


Output
첫 줄에 가능한 보드의 배치 개수를 출력한다.

둘째 줄에 col 배열의 값을 숫자의 문자열로 취급했을 때 최대값을 출력한다.


Sample Input 1

4
Sample Output 1

2
3142
Sample Input 2

12
Sample Output 2

14200
975811210364211*/
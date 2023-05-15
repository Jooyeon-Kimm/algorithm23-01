#include <iostream>
#include <vector>

using namespace std;

int n;  // 원소의 개수
int W;  // 목표 합
vector<int> w;  // 원소들의 값
vector<bool> include;  // 부분집합 포함 여부
vector<vector<int>> res;  // 부분집합 결과 저장

// 유망성 판단 함수
bool promising(int i, int weight, int total) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

// 부분집합 생성을 위한 백트래킹 함수
void sum_of_subsets(int i, int weight, int total, int count) {
    if (promising(i, weight, total)) {
        if (weight == W) {
            vector<int> subset;
            for (int j = 1; j <= i; j++) {
                if (include[j]) {
                    subset.push_back(w[j]);
                }
            }
            res.push_back(subset);
            count++;
        }
        else {
            include[i + 1] = true;
            sum_of_subsets(i + 1, weight + w[i + 1], total - w[i + 1], count);
            include[i + 1] = false;
            sum_of_subsets(i + 1, weight, total - w[i + 1], count);
        }
    }
}

int main() {
    cin >> n >> W;

    w.resize(n + 1);
    include.resize(n + 1);

    int total = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        total += w[i];
    }

    int count = 0;
    sum_of_subsets(0, 0, total, count);

    cout << res.size();
    if (res.size() != 0) cout << endl;

    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j];
            if (j < res[i].size() - 1) cout << " ";
        }
        if (i != res.size() - 1)cout << endl;
    }


    return 0;
}

/*

부분집합의 합 문제
Description

교재와 강의자료를 참고하여 Sum-of-Subsets 문제를 푸는 Algorithm 5.4의 구현을 완성하시오.



n개의 원소를 가진 정수의 집합 S가 주어지고,

임의의 정수 W가 주어졌을 때,

합이 W가 되는 부분집합의 개수와 각 부분집합을 출력하도록 하시오.


Input
첫 줄에 원소의 개수 n과 임의의 정수 W가 주어진다.

둘째 줄에 n개의 정수가 주어진다.


Output
첫 줄에 원소의 합이 W가 되는 부분집합의 개수를 출력한다.

둘째 줄부터 원소의 합이 W가 되는 모든 부분집합을 한 줄에 하나씩 출력한다.

단, 부분집합에서의 원소 출력 순서는 주어진 S의 원소 순서와 동일해야 한다. (백트래킹 순서대로)


Sample Input 1

4 13
3 4 5 6
Sample Output 1

1
3 4 6
Sample Input 2

3 10
1 2 3
Sample Output 2

0
Sample Input 3

20 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
Sample Output 3

64
1 2 3 4 10
1 2 3 5 9
1 2 3 6 8
1 2 3 14
1 2 4 5 8
1 2 4 6 7
1 2 4 13
1 2 5 12
1 2 6 11
1 2 7 10
1 2 8 9
1 2 17
1 3 4 5 7
1 3 4 12
1 3 5 11
1 3 6 10
1 3 7 9
1 3 16
1 4 5 10
1 4 6 9
1 4 7 8
1 4 15
1 5 6 8
1 5 14
1 6 13
1 7 12
1 8 11
1 9 10
1 19
2 3 4 5 6
2 3 4 11
2 3 5 10
2 3 6 9
2 3 7 8
2 3 15
2 4 5 9
2 4 6 8
2 4 14
2 5 6 7
2 5 13
2 6 12
2 7 11
2 8 10
2 18
3 4 5 8
3 4 6 7
3 4 13
3 5 12
3 6 11
3 7 10
3 8 9
3 17
4 5 11
4 6 10
4 7 9
4 16
5 6 9
5 7 8
5 15
6 14
7 13
8 12
9 11
20
*/
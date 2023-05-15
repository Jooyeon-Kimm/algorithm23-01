#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 101;
vector<int> adj[MAXN];
int n, m, k;
bool W[MAXN][MAXN];
int vcolor[MAXN];
int cnt;

void convert_input() {
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }
    memset(W, false, sizeof(W));
    for (int i = 1; i <= n; i++) {
        for (int j : adj[i]) {
            W[i][j] = true;
            W[j][i] = true;
        }
    }
}

bool promising(int i) {
    int j = 1;
    bool flag = true;
    while (j < i && flag) {
        if (W[i][j] && vcolor[i] == vcolor[j]) {
            flag = false;
        }
        j++;
    }
    return flag;
}

void m_coloring(int i) {
    if (promising(i)) {
        if (i == n) {
            cnt++;
            return;
        }
        else {
            for (int color = 1; color <= m; color++) {
                vcolor[i + 1] = color;
                m_coloring(i + 1);
            }
        }
    }
}

int main() {
    convert_input();
    m = 1;
    while (true) {
        bool is_possible = true;
        cnt = 0;
        memset(vcolor, 0, sizeof(vcolor));
        m_coloring(0);
        if (cnt > 0) {
            cout << m << endl << cnt;
            break;
        }
        m++;
    }
    return 0;
}

/*
m-Coloring 문제
Description

교재와 강의자료를 참고하여 m-Coloring 문제를 해결하는 Algorithm 5.5의 구현은 완성하시오.



주어진 평면 그래프 G = (V, E)에 대해서

인접한 지역을 서로 다른 색으로 색칠하기 위해 필요한 최소 색의 수 m의 값과

해당하는 m의 값으로 색칠할 수 있는 경우의 수를 출력하시오.



단,그래프의 입력은 간선의 집합으로 주어지고,주어진 그래프는 평면 그래프라고 가정해도 된다.


Input
첫 줄에 정점의 수 n과 간선의 수 k가 주어진다.

둘째 줄부터 k개의 간선이 주어진다.


Output
첫째 줄에 색칠 가능한 최소의 m값을 출력한다.

둘째 줄에 해당 m값으로 색칠할 수 있는 경우의 수를 출력한다.


Sample Input 1

4 5
1 2
1 3
1 4
2 3
3 4
Sample Output 1

3
6
Sample Input 2

4 6
1 2
1 3
1 4
2 3
2 4
3 4
Sample Output 2

4
24
*/
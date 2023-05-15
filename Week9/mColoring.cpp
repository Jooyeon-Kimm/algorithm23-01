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
m-Coloring ����
Description

����� �����ڷḦ �����Ͽ� m-Coloring ������ �ذ��ϴ� Algorithm 5.5�� ������ �ϼ��Ͻÿ�.



�־��� ��� �׷��� G = (V, E)�� ���ؼ�

������ ������ ���� �ٸ� ������ ��ĥ�ϱ� ���� �ʿ��� �ּ� ���� �� m�� ����

�ش��ϴ� m�� ������ ��ĥ�� �� �ִ� ����� ���� ����Ͻÿ�.



��,�׷����� �Է��� ������ �������� �־�����,�־��� �׷����� ��� �׷������ �����ص� �ȴ�.


Input
ù �ٿ� ������ �� n�� ������ �� k�� �־�����.

��° �ٺ��� k���� ������ �־�����.


Output
ù° �ٿ� ��ĥ ������ �ּ��� m���� ����Ѵ�.

��° �ٿ� �ش� m������ ��ĥ�� �� �ִ� ����� ���� ����Ѵ�.


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
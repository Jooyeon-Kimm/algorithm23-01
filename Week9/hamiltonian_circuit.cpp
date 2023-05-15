#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define MAX 10000
int n, m;
int vindex[MAX];
bool W[MAX][MAX];
int count_hc = 0;

bool promising(int i) {
    int j;
    bool flag;
    if (i == n - 1 && !W[vindex[n - 1]][vindex[0]])
        flag = false;
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
        flag = false;
    else {
        flag = true;
        j = 1;
        while (j < i && flag) {
            if (vindex[i] == vindex[j])
                flag = false;
            j++;
        }
    }
    return flag;
}

void hamiltonian(int i) {
    int j;
    if (promising(i)) {
        if (i == n - 1 && W[vindex[n - 1]][vindex[0]]) {
            count_hc++;
        }
        else
            for (j = 2; j <= n; j++) {
                vindex[i + 1] = j;
                hamiltonian(i + 1);
            }
    }
}

int main() {
    cin >> n >> m;
    vindex[0] = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        W[a][b] = true;
        W[b][a] = true;
    }
    hamiltonian(0);
    cout << count_hc;
    return 0;
}

/*
�ع��� ȸ�� ����
Description

����� �����ڷḦ �����Ͽ� �ع��� ȸ�� ������ �ذ��ϴ� Algorithm 5.6�� ������ �ϼ��Ͻÿ�.



�־��� ������ ������ġ �׷��� G = (V, E) ����

�ع��� ȸ���� ������ ����Ͻÿ�.



Algorithm 5.6�� ������ ��, ��������� 1�� �����Ѵٴ� ���� �����Ͻÿ�.

vindex[0] = 1;

hamiltonian(0);


Input
ù° �ٿ� ������ ���� n�� ������ ���� m�� �־�����.

��° �ٺ��� m���� ������ �־�����.


Output
ù° �ٿ� �ع��� ȸ���� ������ ����Ѵ�.


Sample Input 1

8 13
1 2
1 3
1 7
1 8
2 3
2 7
2 8
3 4
3 6
4 5
5 6
6 7
7 8
Sample Output 1

8
Sample Input 2

5 6
1 2
1 5
2 3
2 4
2 5
3 4
Sample Output 2

0
*/
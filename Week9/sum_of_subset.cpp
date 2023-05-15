#include <iostream>
#include <vector>

using namespace std;

int n;  // ������ ����
int W;  // ��ǥ ��
vector<int> w;  // ���ҵ��� ��
vector<bool> include;  // �κ����� ���� ����
vector<vector<int>> res;  // �κ����� ��� ����

// ������ �Ǵ� �Լ�
bool promising(int i, int weight, int total) {
    return (weight + total >= W) && (weight == W || weight + w[i + 1] <= W);
}

// �κ����� ������ ���� ��Ʈ��ŷ �Լ�
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

�κ������� �� ����
Description

����� �����ڷḦ �����Ͽ� Sum-of-Subsets ������ Ǫ�� Algorithm 5.4�� ������ �ϼ��Ͻÿ�.



n���� ���Ҹ� ���� ������ ���� S�� �־�����,

������ ���� W�� �־����� ��,

���� W�� �Ǵ� �κ������� ������ �� �κ������� ����ϵ��� �Ͻÿ�.


Input
ù �ٿ� ������ ���� n�� ������ ���� W�� �־�����.

��° �ٿ� n���� ������ �־�����.


Output
ù �ٿ� ������ ���� W�� �Ǵ� �κ������� ������ ����Ѵ�.

��° �ٺ��� ������ ���� W�� �Ǵ� ��� �κ������� �� �ٿ� �ϳ��� ����Ѵ�.

��, �κ����տ����� ���� ��� ������ �־��� S�� ���� ������ �����ؾ� �Ѵ�. (��Ʈ��ŷ �������)


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
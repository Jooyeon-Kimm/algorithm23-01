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
n-Queens ����
Description

����� �����ڷḦ �����Ͽ�n-Queens ������ �ذ��ϴ�Algorithm 5.1�� �ϼ��Ͻÿ�.



n�� ���� �־��� ��, n-Queens ������ �ذ��ϴ� ������ ��ġ�� �� �� �������� ī��Ʈ�ϰ�,

col �迭�� ���� ������ ���ڿ��� ������� �� ���� ū ���� ����ϵ��� �����Ͻÿ�.

��)

n = 4�� �� ������ ������ ��ġ�� ������ ���� �� 2���� �ִ�.

col1 = [2, 4, 1, 3]

col2 = [3, 1, 4, 2]

�� ��ġ�� col �迭�� ������ ���ڿ��� ����ϸ� ���� 2413, 3142�� ���� ���´�.

���� �� ������ ����� ������ ����.

2 ; ������ ���� ��ġ�� ����

3142 ; ������ ���� ��ġ �߿��� ������ ���ڿ��� ���� ū ��


Input
ù �ٿ� n�� ���� �־�����.

��, n�� 4���� ũ�ų� ����.


Output
ù �ٿ� ������ ������ ��ġ ������ ����Ѵ�.

��° �ٿ� col �迭�� ���� ������ ���ڿ��� ������� �� �ִ밪�� ����Ѵ�.


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
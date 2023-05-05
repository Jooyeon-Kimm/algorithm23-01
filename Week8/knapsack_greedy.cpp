#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct item* item_ptr;
typedef struct item {
    int id;
    int weight;
    int profit;
    int profit_per_unit; // = profit / weight
} item_t;

bool compare_item(item_t i, item_t j) {
    if (i.profit_per_unit > j.profit_per_unit)
        return true;
    return false;
};

/* Greedy Algorithm for the Fractional Knapsack Problem */
void knapsack(int& maxprofit, int& totweight, vector<item_t>& items, int W) {
    maxprofit = totweight = 0;
    int n = items.size();
    for (int i = 0; i < n; i++) {
        if (totweight + items[i].weight <= W) {
            maxprofit += items[i].profit;
            totweight += items[i].weight;
        }
        else {
            maxprofit += (W - totweight) * items[i].profit_per_unit;
            totweight += (W - totweight);
            break; // need not to be continued.
        }
    }
}

int main() {
    int n, T;
    cin >> n;   // �������� ����

    vector<item_t> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight; // �������� ���� �Է�
    }

    for (int i = 0; i < n; i++) {
        cin >> items[i].profit; // �������� �̵� �Է�
        items[i].id = i + 1;
        items[i].profit_per_unit = items[i].profit / items[i].weight;
    }

    // item�� profit_per_unit�� �������� �������� ����
    sort(items.begin(), items.end(), compare_item);

    // �賶 ���� W�� ���� T
    cin >> T;
    for (int i = 0; i < T; i++) {
        int W;
        cin >> W;   // �賶�� ����

        int maxprofit, totweight;
        knapsack(maxprofit, totweight, items, W);

        cout << maxprofit << endl;

        int n = items.size();
        for (int j = 0; j < n; j++) {
            if (totweight == 0) break;
            if (items[j].weight <= totweight) {
                cout << items[j].weight << " " << items[j].profit << endl;
                totweight -= items[j].weight;
            }
            else {
                cout << totweight << " " << (int)(items[j].profit_per_unit * totweight) << endl;
                totweight = 0;
            }
        }
    }

    return 0;
}

/*

Description

���Ұ����� �賶 ������ �ذ��ϴ� 
Ž�� �˰����� ������ �ϼ��Ͻÿ�.

�Է��� �������� ���Կ� ������ �־�����,
Ž�� �˰����� ���� ���Դ� ������ ���� ���� ������� 
�賶�� ��� ������ ���Ѵ�.

�Է����� �־����� ���� 
���� ���Դ� �������� ���ĵǾ� ���� ������ �����϶�.

��, ���� ���Դ� ������ ���� �������� ���ٰ� �����ص� �ȴ�.


Input
ù° �ٿ� �������� ���� n�� �־�����.
��° �ٿ� n���� �������� ���԰� �־�����.
��° �ٿ� n���� �����ۺ� ������ �־�����.
��° �ٿ� ������ �賶 ���� W�� ���� T�� �־�����.
�ټ�° �ٺ��� T���� �賶 ���� W�� �־�����.


Output
�Է����� �־��� �� W�� ���ؼ�
ù �ٿ� Ž������� �賶�� ���� �� �ִ� �ִ������� ����Ѵ�.

��° �ٺ��� �賶�� ���� �������� ������� 
���Կ� ������ ���� �� �ٿ� �ϳ��� ����Ѵ�.

���� �ٿ��� ������ �־����� W�� ���ؼ� 
���� ����� �ݺ��Ѵ�.


Sample Input 1

3
5 10 20
50 60 140
1
30
Sample Output 1

220
5 50
20 140
5 30
Sample Input 2

4
2 5 10 5
40 30 50 10
4
8
16
20
25
Sample Output 2

75
2 40
5 30
1 5
115
2 40
5 30
9 45
126
2 40
5 30
10 50
3 6
130
2 40
5 30
10 50
5 10

*/
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
    cin >> n;   // 아이템의 개수

    vector<item_t> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight; // 아이템의 무게 입력
    }

    for (int i = 0; i < n; i++) {
        cin >> items[i].profit; // 아이템의 이득 입력
        items[i].id = i + 1;
        items[i].profit_per_unit = items[i].profit / items[i].weight;
    }

    // item을 profit_per_unit을 기준으로 내림차순 정렬
    sort(items.begin(), items.end(), compare_item);

    // 배낭 무게 W의 개수 T
    cin >> T;
    for (int i = 0; i < T; i++) {
        int W;
        cin >> W;   // 배낭의 무게

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

분할가능한 배낭 문제를 해결하는 
탐욕 알고리즘의 구현을 완성하시오.

입력은 아이템의 무게와 이익이 주어지고,
탐욕 알고리즘은 단위 무게당 이익이 가장 높은 순서대로 
배낭에 담는 전략을 취한다.

입력으로 주어지는 값은 
단위 무게당 이익으로 정렬되어 있지 않음에 주의하라.

단, 단위 무게당 이익이 같은 아이템은 없다고 가정해도 된다.


Input
첫째 줄에 아이템의 개수 n이 주어진다.
둘째 줄에 n개의 아이템의 무게가 주어진다.
셋째 줄에 n개의 아이템별 이익이 주어진다.
넷째 줄에 도둑의 배낭 무게 W의 개수 T가 주어진다.
다섯째 줄부터 T개의 배낭 무게 W가 주어진다.


Output
입력으로 주어진 각 W에 대해서
첫 줄에 탐욕법으로 배낭에 담을 수 있는 최대이익을 출력한다.

둘째 줄부터 배낭에 담은 아이템의 순서대로 
무게와 이익의 쌍을 한 줄에 하나씩 출력한다.

다음 줄에는 다음에 주어지는 W에 대해서 
위의 출력을 반복한다.


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
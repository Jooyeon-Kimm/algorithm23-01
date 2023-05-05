#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef pair<int, int> edge;
typedef vector<int> v1;
typedef vector<v1> v2;

int V, E;
int s, e, w;

void print_nearest(v1& arr) {
    for (int i = 2; i <= V; i++) {
        cout << arr[i];
        if (i < V) cout << endl;
    }       
}

void print_edges(v2& W, vector<edge>& F) {
    for (int i = 0; i < F.size(); i++) {
        s = F[i].first;
        e = F[i].second;
        cout << s << " " << e << " " << W[s][e];
        if (i != F.size() - 1) cout << endl;
    }
}

void prim(v2& W, vector<edge>& F) {

    // 1. 변수 선언
    int vnear, min;
    v1 nearest(V + 1, 0);
    v1 distance(V + 1, 0);

    // 2. v1을 시작정점으로 설정 후 초기화
    for (int i = 2; i <= V; i++) {
        nearest[i] = 1;
        distance[i] = W[1][i];
    }
    print_nearest(nearest);

    // 3. 프림 알고리즘
    for (int i = 2; i <= V; i++) {
        // 3-1. 가장 가까운 정점찾기
        min = INF;
        for (int j = 2; j <= V; j++)
            if (0 <= distance[j] && distance[j] < min) {
                min = distance[j];
                vnear = j;
            }
        // 3-2. 가장 가까운 정점을 추가
        F.push_back(make_pair(vnear, nearest[vnear]));
        distance[vnear] = -1;

        // 3-3. 추가된 정점을 반영하여 업데이트
        for (int j = 2; j <= V; j++)
            if (distance[j] > W[j][vnear]) {
                distance[j] = W[j][vnear];
                nearest[j] = vnear;
            }

        print_nearest(nearest);
    }
}

int main() {

    cin >> V >> E;
    vector<edge> F;
    v2 W(V + 1, v1(V + 1, INF));
    for (int i = 1; i <= V; i++) W[i][i] = 0;

    for (int i = 0; i < E; i++) {
        cin >> s >> e >> w;
        W[s][e] = W[e][s] = w;
    }

    prim(W, F);

    print_edges(W, F);

    return 0;
}
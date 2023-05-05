#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x7fffffff
#define lint long long int 
using namespace std;
typedef pair<int, int> edge;
typedef vector<int> v1;
typedef vector<lint> v1_long;
typedef vector<v1> v2;

int V, E, n;
int s, e, w, t;

void print_arr(v2& arr) {
    cout << "printing ARR" << endl;
    for (int i = 1; i < arr.size(); i++) {
        for (int j = 1; j < arr[0].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void print_touch(v1& arr) {
    for (int i = 2; i <= V; i++) {
        cout << arr[i];
        if (i < V)cout << endl;
    }
}

void print_edges(v2& W, vector<edge>& F) {
    for (int i = 0; i < F.size(); i++) {
        s = F[i].first;
        e = F[i].second;
        cout << s << " " << e << " " << W[s][e] << endl;
    }
}

void print_path(int e, v1& path) {
    if (e == 1) return;
    print_path(path[e], path);
    cout << path[e] << " ";
}

v1 dijkstra(v2& W, vector<edge>& F) {

    // 1. 변수 선언
    lint vnear, min;
    v1 touch(V + 1, 0);
    v1_long length(V + 1, 0);

    // 2. v1을 시작정점으로 설정 후 초기화
    for (int i = 2; i <= V; i++) {
        touch[i] = 1;
        length[i] = W[1][i];
    }
    print_touch(touch);

    // 3. 다익스트라
    for (int i = 2; i <= V; i++) {
        // 3-1. 가장 가까운 정점찾기
        min = INF;
        for (int j = 2; j <= V; j++)
            if (0 <= length[j] && length[j] < min) {
                min = length[j];
                vnear = j;
            }
        // 3-2. 가장 가까운 정점을 추가
        F.push_back(make_pair(touch[vnear], vnear));

        // 3-3. 추가된 정점을 반영하여 업데이트
        for (int j = 2; j <= V; j++)
            if (length[j] > W[vnear][j] + length[vnear]) {
                length[j] = W[vnear][j] + length[vnear];
                touch[j] = vnear;
            }

        length[vnear] = -1;
        print_touch(touch);
    }
    return touch;
}


int main() {

    cin >> V >> E;
    vector<edge> F;
    v2 W(V + 1, v1(V + 1, INF));
    for (int i = 1; i <= V; i++) W[i][i] = 0;

    for (int i = 0; i < E; i++) {
        cin >> s >> e >> w;
        W[s][e] = w;
    }

    v1 path = dijkstra(W, F);
    print_edges(W, F);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t;
        print_path(t, path);
        if (i < i - 1) cout << endl;
    }

    return 0;
}
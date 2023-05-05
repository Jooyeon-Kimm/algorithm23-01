#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

#define INF 0xffff
typedef vector<int> v1;
typedef vector<v1> v2;
typedef pair<int, int> edge;
typedef vector<edge> edge_set;
typedef vector<pair< int, edge>> edge_weight;

v1 dset; // disjoint set (초기: 서로소 집합)
edge_set E, F;

void dest_print(int n) {
	for (int i = 1; i <= n; i++) {
		cout << dset[i] << " ";
	}
}
// n개의 연결되지 않은 subset 초기화
// initialzes 𝑛 disjoint subsets.
void dset_init(int n) {
	dset.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		dset[i] = i;
	}
}

// p = find (i);
// makes 𝑝 point to the set containing index 𝑖.
// i가 속한 집합의 대푯값을 반환한다.
// 즉, x가 어떤 집합에 속해 있는지 찾아주는 연산
// 트리를 이용해서 구현하므로 대푯값은 노드 번호를 의미한다.
int dset_find(int i) {
	while (dset[i] != i) {
		i = dset[i];
	}
	return i;
}

// 두 집합을 연결
// merges the two sets, to which 𝑝 and 𝑞 point, into the set.
void dset_merge(int p, int q) {
	dset[p] = q;
}

// 크루스칼 알고리즘
void kruskal(int n, int m, edge_set& E, edge_set& F) {
	int p, q;
	edge e;

	priority_queue <edge> PQ;
	// sort the m edges in E by weight in nondecreasing order;

	F.clear(); // 𝐹 = ∅;
	dset_init(n);

	while (F.size() < n - 1) { // number of edges in F is less than n - 1
		e = PQ.top();
		PQ.pop(); // edge with least weight not yet considered;
		// 가중치가 가장 작은 간선은 어차피 들어가니까 고려하지 않음

		p = dset_find(e.first);		// e.u
		q = dset_find(e.second);	// e.v
		if (p != q) {
			dset_merge(p, q);
			F.push_back(e); // add e to F
		}
	}
}


int main(void) {
	// 첫 줄에 정점의 개수 n, 간선의 개수 m이 주어진다.
	int n, m;
	cin >> n >> m;


	// W : 정점 사이의 가중치 저장
	// W[1][2] = 3 이면, 정점 1과 정점 2 사이의 가중치는 3...
	v2 W(n + 1, v1(n + 1, INF));
	for (int i = 1; i <= n; i++) {
		W[i][i] = 0; // 자기 자신에서 나와서 자기 자신으로 들어가면 Weight는 0
	}


	// 두 번째 줄부터 다음과 같은 형태로 m 개의 간선이 주어진다.
	// u v w
	// u와 v는 정점의 번호이고, 1부터 n까지의 자연수로 표시한다.
	// w는 간선 <u, v>의 가중치이며, 양의 정수 값으로 주어진다.
	int u, v, w;
	edge_weight edges;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> w;
		edges.push_back({ w, {u, v} });
	}

	//간선을 가중치 기준 오름차순으로 정렬
	sort(edges.begin(), edges.end());
	
	// 잘 정렬되었는지 (u, v, w) 순서로 출력해보기
	for (int i = 0; i < m; i++) {
		cout << edges[i].second.first << " ";	// u
		cout << edges[i].second.second << " ";	// v
		cout << edges[i].first << endl;			// w
	}

	kruskal(n, m, E, F);
	cout << endl << "끝" << endl << endl;

	return 0;
}

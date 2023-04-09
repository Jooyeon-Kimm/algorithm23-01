// Floyd Warshal Algorithm
// 중간 노드를 거쳐가는 weight와
// 시작 노드에서 끝 노드까지 바로 갈 때 weight
// 비교해서 작은 값을 P에 업데이트

#include <iostream>
#include <vector>
#include <algorithm> // min
#define INF 999

using namespace std;
typedef vector<int> v1;
typedef vector<vector<int>> v2;

// Floyd’s Algorithm for Shortest Paths 2
void floyd(int n, v2& W, v2& D, v2& P)
{
	// D를 인접리스트로 초기화
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			D[i][j] = W[i][j];
			P[i][j] = 0;
		}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				// i > k > j 로 k를 거쳐가는 경로의 weight가
				// i > k 로 k를 거치지 않는 경로의 weight 보다 작을 때 (최적일 때)
				// D 업데이트하고 P를 k로 업데이트
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
}


// 중위순회 (inorder traversal)
// s과 e는 출력하지 않아서 따로 처리해줘야 함
// ppt에는 path함수의 인수에 일차원 벡터 p가 있다.
// 일차원 벡터 p에 push_back()으로 경로를 저장하는 코드였으나
// 그러면 입력받은 sePairs에 대한 1차 for문 안에서
// 2차 for문을 돌면서 출력하게 돼서
// 일차원 벡터 p를 함수 인수에서 제거함
void path(v2& P, int s, int e) {
	if (P[s][e] == 0) return;
	path(P, s, P[s][e]);
	cout << P[s][e] << " ";
	path(P, P[s][e], e);
}

void printPath(v2& sePairs, v2& D, v2&P) {
	for (int i = 0; i < sePairs.size(); i++) {
		int s = sePairs[i][0];
		int e = sePairs[i][1];

		if (D[s][e] == INF) {
			cout << "NONE" << endl;
		}

		else {
			cout << s << " ";
			path(P, s, e);
			cout << e << endl;
		}
	}
}

// print 2d table
void print2D(int n, v2& v) {
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= n; k++) {
			cout << v[i][k];
			if (k == n) cout << endl;
			else cout << " ";
		}
	}
}

int main()
{
	// number of vertices N, number of edges M
	int n, m;
	cin >> n >> m;

	// W: adjacency matrix (인접행렬), if no edge: INF
	// D: result table (결과테이블)
	// P: calculation procedure matrix (D 계산 기록하는 매트릭스)
	v2 W(n + 1, v1(n + 1, INF));
	v2 D(n + 1, v1(n + 1));
	v2 P(n + 1, v1(n + 1));

	// 자기자신에서 본인으로 가는 경로: 0
	for (int i = 1; i <= n; i++) {
		W[i][i] = 0;
	}

	// W (u, v, w)
	// u: starting vertex
	// v: ending vertex
	// w: weight of the edge
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		W[u][v] = w;
	}
	
	// Floyd Warshall Algorithm
	floyd(n, W, D, P);


	// print the table D
	print2D(n, D);

	// print the matrix P
	print2D(n, P);

	// number of SE pairs T (starting vertex and ending vertex)
	int t;
	cin >> t;
	v2 sePairs(t, v1(2));

	for (int i = 0; i < t; i++) {
		int s, e;
		cin >> s >> e;
		sePairs[i][0] = s;
		sePairs[i][1] = e;
	}

	// print out the shortest path
	printPath(sePairs, D, P);


	return 0;
}



/*
Description

교재와 강의자료를 참고하여 Algorithm 3.4/3.5 Floyd2 알고리즘의 구현을 완성하시오.



이 문제에서는 주어진 가중치가 있는 방향 그래프에서 
모든 쌍 최단경로를 찾는 플로이드 알고리즘을 수행하고,
알고리즘의 결과물인 D 테이블과 P 테이블을 출력한다.

또한, 주어진 D의 출발 정점과 도착 정점에 대해서 최단 경로를 출력한다.
D 테이블에서 경로가 없는 정점에 대해서는 INF = 999 를 출력하도록 한다.
#define INF 999


경로를 출력할 때는 출발 정점과 도착 정점도 함께 표시해야 하고,
경로가 존재하지 않는 두 정점에 대해서는 NONE 이라고 표시하도록 한다.
출발 정점과 도착 정점이 같은 경우에는 출발 정점과 도착 정점을 따로 표시하면 된다.


Input
첫 번째 줄에 정점의 개수 N과 간선의 개수 M이 주어진다.
정점의 번호는 1번부터 N번까지로 정한다.
두 번째 줄부터 M개의 간선의 정보가 주어진다.
각 간선의 정보 u v w는 각각 간선의 출발 정점 u, 도착 정점 v, 해당 간선의 가중치 w로 주어진다.
모든 간선의 정보가 주어진 후에 다음 줄에 출발/도착 정점의 쌍의 개수 T가 주어진다.
그 다음 줄부터 T개의 출발/도착 정점의 쌍이 주어진다.


Output
먼저, N * N 행렬 D를 출력한다.
다음에 N * N 행렬 P를 출력한다.
D와 P는 floyd2() 함수의 결과값이다.
D와 P 행렬의 출력 이후로 T 개의 최단 경로를 출력한다.
최단 경로는 출발 정점에서 시작하여 중간 정점을 모두 출력하고 도착 정점을 출력한다.
만약 출발 정점에서 도착 정점으로의 경로가 존재하지 않으면 NONE 이라고 출력한다.
*/
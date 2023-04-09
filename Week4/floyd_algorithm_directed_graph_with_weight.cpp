// Floyd Warshal Algorithm
// �߰� ��带 ���İ��� weight��
// ���� ��忡�� �� ������ �ٷ� �� �� weight
// ���ؼ� ���� ���� P�� ������Ʈ

#include <iostream>
#include <vector>
#include <algorithm> // min
#define INF 999

using namespace std;
typedef vector<int> v1;
typedef vector<vector<int>> v2;

// Floyd��s Algorithm for Shortest Paths 2
void floyd(int n, v2& W, v2& D, v2& P)
{
	// D�� ��������Ʈ�� �ʱ�ȭ
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			D[i][j] = W[i][j];
			P[i][j] = 0;
		}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				// i > k > j �� k�� ���İ��� ����� weight��
				// i > k �� k�� ��ġ�� �ʴ� ����� weight ���� ���� �� (������ ��)
				// D ������Ʈ�ϰ� P�� k�� ������Ʈ
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = k;
				}
}


// ������ȸ (inorder traversal)
// s�� e�� ������� �ʾƼ� ���� ó������� ��
// ppt���� path�Լ��� �μ��� ������ ���� p�� �ִ�.
// ������ ���� p�� push_back()���� ��θ� �����ϴ� �ڵ忴����
// �׷��� �Է¹��� sePairs�� ���� 1�� for�� �ȿ���
// 2�� for���� ���鼭 ����ϰ� �ż�
// ������ ���� p�� �Լ� �μ����� ������
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

	// W: adjacency matrix (�������), if no edge: INF
	// D: result table (������̺�)
	// P: calculation procedure matrix (D ��� ����ϴ� ��Ʈ����)
	v2 W(n + 1, v1(n + 1, INF));
	v2 D(n + 1, v1(n + 1));
	v2 P(n + 1, v1(n + 1));

	// �ڱ��ڽſ��� �������� ���� ���: 0
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

����� �����ڷḦ �����Ͽ� Algorithm 3.4/3.5 Floyd2 �˰����� ������ �ϼ��Ͻÿ�.



�� ���������� �־��� ����ġ�� �ִ� ���� �׷������� 
��� �� �ִܰ�θ� ã�� �÷��̵� �˰����� �����ϰ�,
�˰����� ������� D ���̺�� P ���̺��� ����Ѵ�.

����, �־��� D�� ��� ������ ���� ������ ���ؼ� �ִ� ��θ� ����Ѵ�.
D ���̺��� ��ΰ� ���� ������ ���ؼ��� INF = 999 �� ����ϵ��� �Ѵ�.
#define INF 999


��θ� ����� ���� ��� ������ ���� ������ �Բ� ǥ���ؾ� �ϰ�,
��ΰ� �������� �ʴ� �� ������ ���ؼ��� NONE �̶�� ǥ���ϵ��� �Ѵ�.
��� ������ ���� ������ ���� ��쿡�� ��� ������ ���� ������ ���� ǥ���ϸ� �ȴ�.


Input
ù ��° �ٿ� ������ ���� N�� ������ ���� M�� �־�����.
������ ��ȣ�� 1������ N�������� ���Ѵ�.
�� ��° �ٺ��� M���� ������ ������ �־�����.
�� ������ ���� u v w�� ���� ������ ��� ���� u, ���� ���� v, �ش� ������ ����ġ w�� �־�����.
��� ������ ������ �־��� �Ŀ� ���� �ٿ� ���/���� ������ ���� ���� T�� �־�����.
�� ���� �ٺ��� T���� ���/���� ������ ���� �־�����.


Output
����, N * N ��� D�� ����Ѵ�.
������ N * N ��� P�� ����Ѵ�.
D�� P�� floyd2() �Լ��� ������̴�.
D�� P ����� ��� ���ķ� T ���� �ִ� ��θ� ����Ѵ�.
�ִ� ��δ� ��� �������� �����Ͽ� �߰� ������ ��� ����ϰ� ���� ������ ����Ѵ�.
���� ��� �������� ���� ���������� ��ΰ� �������� ������ NONE �̶�� ����Ѵ�.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef vector<int> v1;
typedef vector<v1> v2;
#define INF 999999


int minimum(int i, int j, int& mink, v1& P, v2& A) {
	int minValue = INF, value;

	int pSum = 0;
	for (int m = i; m <= j; m++) {
		pSum += P[m];
	}
	for (int k = i; k <= j ; k++) {
		value = A[i][k - 1] + A[k + 1][j] + pSum;

		if (minValue > value) {
			minValue = value;
			mink = k;
		}
	}
	return minValue;
}


void optsearchtree(int n, v1& P, v2& A, v2& R)
{
	int i, j, k, diagonal, pSum = 0;

	for (i = 1; i <= n; i++) {
		A[i][i - 1] = 0; A[i][i] = P[i];
		R[i][i - 1] = 0; R[i][i] = i;
	}
	A[n + 1][n] = R[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {
		for (i = 1; i <= n - diagonal; i++) {
			j = i + diagonal;
			A[i][j] = minimum(i, j, k, P, A);
			R[i][j] = k;
		}
	}

	
}

typedef struct node_type* node_ptr;
struct node_type
{
	int data;
	node_ptr left;
	node_ptr right;
};

node_ptr create_node(int data)
{
	node_ptr new_node = (node_ptr)malloc(sizeof(node_type));
	if (new_node == NULL)
	{
		puts("Memory Allocation Error");
		exit(1);
	}

	new_node->data = data;
	new_node->right = NULL;

	return new_node;
}

node_ptr tree(int i, int j, v1& keys, v2& R)
{
	int k = R[i][j];
	if (k == 0)
		return NULL;
	else {
		node_ptr node = create_node(keys[k]);
		node->left = tree(i, k - 1, keys, R);
		node->right = tree(k + 1, j, keys, R);
		return node;
	}
}

int cnt = 0;
void preorder(int n, node_ptr node){

	if (node){
		cnt++;

		if (cnt == n) { // �������� ���� ��µǸ� �ȵ�...
			printf("%d", node->data);
		}
		else {
			printf("%d ", node->data);
		}

		preorder(n, node->left);
		preorder(n, node->right);
	}
}

void inorder(int n, node_ptr node) {
	if (node) {

		inorder(n, node->left);
		cnt++;

		if (cnt == n) { // �������� ���� ��µǸ� �ȵ�...
			printf("%d", node->data);
		}
		else {
			printf("%d ", node->data);
		}

		inorder(n, node->right);
	}
}
void printMatrix(int n, v2& arr) {
	for (int i = 1; i <= n + 1; i++) {
		cout << "0";
		for (int k = i; k <= n; k++) {
			cout << " " << arr[i][k];
			if (k == n) cout << endl;
		}
	}
	cout << endl;
}


int main(void) {

	// ù° �ٿ� key�� ���� n�� �־�����.
	int n; 
	cin >> n;

	v1 keys(n + 1, 0);	// key ��
	v1 P(n + 1, 0);		// �󵵰�

	// ��° �ٿ� n ���� key ���� �־�����. (key ���� ���ĵǾ� �ִٰ� �����ص� �ȴ�.)
	for (int i = 1; i <= n; i++) {
		cin >> keys[i];
	}

	// ��° �ٿ� n ���� �󵵰� p�� �־�����. (p[i] ���� ���� ���������� �־�����.)
	for (int i = 1; i <= n; i++) {
		cin >> P[i];
	}

	v2 A(n + 2, v1(n + 2, INF)); 
	v2 R(n + 2, v1(n + 2, 0)); 



	optsearchtree(n, P, A, R);

	// ���� ��� A�� �� �κ� �ﰢ���� ����Ѵ�. (0�� ����)
	printMatrix(n, A);

	// �������� ��� R�� �� �κ� �ﰢ���� ����Ѵ�. (0�� ����)
	printMatrix(n, R);

	// A�� R�� ����� �Ŀ� ���� ����Ž��Ʈ������ ��հ˻��ð��� �������� ����Ѵ�.
	cout << A[1][n] << endl;

	// ���� ����Ž��Ʈ�� ����
	node_ptr node = tree(1, n, keys, R);

	// ���� �ٿ� ���� ����Ž��Ʈ���� preorder ��ȸ Ž�� ����� ����Ѵ�.
	preorder(n, node);
	cnt = 0;
	cout << endl;

	// ���� �ٿ� ���� ����Ž��Ʈ���� inorder ��ȸ Ž�� ����� ����Ѵ�.
	inorder(n, node);

	
}
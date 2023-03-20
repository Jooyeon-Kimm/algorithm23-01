/*
Input:
6
10 7 11 5 13 8

Output:
5 8 13
*/
#include <algorithm>
#include <vector>
using namespace std;

int main(void) {
	int n;
	scanf("%d", &n);
	
	vector<int> S(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &S[i]);

	sort(S.begin()+1, S.end());

	/* Mathematical Definition of Median
	int median;
	int middle = (n / 2) + 1;
	if (n % 2 == 0) median = (S[middle] + S[middle - 1]) / 2;
	else median = S[middle];
	*/

	printf("%d %d %d", S[1], S[n/2], S[n]);
}
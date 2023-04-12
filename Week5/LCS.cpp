#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<int> v1;
typedef vector<vector<int>> v2;

// Longest Common Subsequence
// 최장공통부분서열 개수
int lcs(string s1, string s2, v2& DP) {
	int len1 = s1.length();
	int len2 = s2.length();

	for (int i = 1; i <= len1; i++) {
		for (int k = 1; k <= len2; k++) {
			if (s1[i - 1] == s2[k - 1])
				DP[i][k] = DP[i - 1][k - 1] + 1;
			else
				DP[i][k] = max(DP[i - 1][k], DP[i][k - 1]);
		}
	}

	return DP[len1][len2];
}

// DP 벡터의 대각선과 대각선 위쪽, 대각선 왼쪽을 확인하면 된다
void get_lcs(v2& DP, string s1, string s2, vector<char>& result) {
	int i = s1.length();
	int k = s2.length();

	while (i>0 && k>0) {
		// cout << "i: " << i << " k: " << k << " s2: " << s2[i - 1] << endl;

		int up = DP[i - 1][k];
		int up_left = DP[i - 1][k - 1];
		int left = DP[i][k - 1];
		int cur = DP[i][k];


		if (cur == up) {
			i--;
		}
		else if (cur == left) {
			k--;
		}
		
		else { // cur != up AND cur != left
			if (cur > up_left) {
				result.push_back(s1[i-1]);
				i--;
				k--;
			}
		}

	}
	

}

void printDP(v2& DP, int len1, int len2) {

	for (int i = 0; i <= len1; i++) {
		for (int k = 0; k <= len2; k++) {
			cout << DP[i][k] << " ";
		}
		cout << endl;
	}
}

int main(void) {
	string s1, s2;
	cin >> s1 >> s2;

	int len1 = s1.length();
	int len2 = s2.length();
	

	v2 DP(len1+1, v1(len2+1, 0));	// DP 벡터
	
	int lcs_len = lcs(s1, s2, DP);
	cout << lcs_len << endl;


	// printDP(DP, len1, len2);
	
	vector<char> result;
	get_lcs(DP, s1, s2, result);

	for (int i = result.size()-1; i >=0; i--) {
		cout << result[i];
	}

	return 0;
}

/*
int lcs(string s1, string s2) {
	int len1 = s1.length();
	int len2 = s2.length();

	// s3, s4: remove the last char
	string s3 = s1.substr(0, len1 - 1); // 인덱스 0부터 len1-1개 문자까지
	string s4 = s2.substr(0, len2 - 1);

	if (len1 == 0 || len2 == 0) return 0;
	else {
		if (s1[len1 - 1] == s2[len2 - 1]) {
			return (lcs(s3, s4) + 1);
		}
		else {
			return max(lcs(s1, s4), lcs(s3, s2));
		}
	}
}
*/
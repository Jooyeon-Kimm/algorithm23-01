#include <iostream>
#include <vector>

using namespace std;
int cnt = 0;

// function to calculate binomial coefficient using recursion and memoization
int bin(int n, int k, vector<vector<int>>& memo) {
    cnt++;
    if (k == 0 || k == n) {
        memo[n][k] = 1;
        return 1;
    }
    if (memo[n][k] != -1) {
        return memo[n][k];
    }
    memo[n][k] = (bin(n - 1, k - 1, memo) + bin(n - 1, k, memo)) % 10007;
    return memo[n][k];
}

// main function to test the binomialCoefficient function
int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> memo(n + 1, vector<int>(k + 1, -1)); // memoization matrix
    int result = bin(n, k, memo);
    cout << result << endl << cnt;

    return 0;
}
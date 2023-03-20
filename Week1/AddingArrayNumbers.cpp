/*
Input:
6
10 7 11 5 13 8

Output:
54
*/
#include <vector>
using namespace std;

int sum(int n, vector<int> S) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result += S[i];
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<int> S(n + 1);

    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);

    printf("%d", sum(n, S));
}
/*
Input:
6
10 7 11 5 13 8

Output:
5 7 8 10 11 13
*/
#include <vector>
using namespace std;

void exchange(int n, vector<int>& S) {
    int temp;

    for (int i = 1; i < n; i++) {
        for (int k = i + 1; k <= n; k++) {
            if (S[i] > S[k]) {
                temp = S[i];
                S[i] = S[k];
                S[k] = temp;

            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    vector<int> S(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);

    exchange(n, S);

    for (int i = 1; i <= n; i++)
        if (i < n)
            printf("%d ", S[i]);
        else
            printf("%d\n", S[i]);
}
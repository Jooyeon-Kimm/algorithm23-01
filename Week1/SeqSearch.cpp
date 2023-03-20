/*
Input:
6 3
10 7 11 5 13 8
5 8 3

Output:
5 is in 4.
8 is in 6.
3 is not in S.
*/

#include <vector>
using namespace std;

void seqsearch(int n, vector<int> S, int x, int& location) {
    location = 0;
    while (S[location] != x && location < n) {
        location++;
    }
    if (location == n) {
        if (S[location] == x) location += 0;
        else location = 0;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> S(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &S[i]);
    }

    while (m--) {
        int x, location;
        scanf("%d", &x);

        seqsearch(n, S, x, location);

        if (location > 0)
            printf("%d is in %d.\n", x, location);
        else
            printf("%d is not in S.\n", x);
    }
}
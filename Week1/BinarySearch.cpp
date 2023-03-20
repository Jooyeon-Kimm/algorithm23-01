/*
Input:
6 3
10 7 11 5 13 8
5 8 3

Output:
5 is in 1.
8 is in 3.
3 is not in S.
*/
#include <vector>
#include <algorithm>
using namespace std;

void binsearch(int n, vector<int> S, int x, int& location) {

    int low = 1, high = n;
    int middle;
    location = 0;

    while (low <= high) {
        middle = (low + high) / 2;

        if (x < S[middle]) 
            high = middle - 1; 

        else if (x > S[middle]) 
            low = middle + 1;

        else {
            location = middle;
            break;
        }
    }    
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> S(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &S[i]);

    sort(S.begin() + 1, S.end());
    for (int i = 1; i <= n; i++)
        printf("%d ", S[i]);
    printf("\n\n");

    while (m--) {
        int x, location;
        scanf("%d", &x);

        binsearch(n, S, x, location);

        if (location > 0)
            printf("%d is in %d.\n", x, location);
        else
            printf("%d is not in S.\n", x);
    }
}
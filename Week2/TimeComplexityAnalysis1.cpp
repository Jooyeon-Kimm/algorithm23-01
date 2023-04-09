/*
Input: 1
Output: 2

Input: 4
Output: 32

Input: 1024
Output: 2097152

*/
#include <iostream>
using namespace std;

typedef long long longType;

longType fun(longType n) {
    longType cnt = 0;
    cnt = 2 * n * n;
    return cnt;
}

int main() {
    longType n;
    cin >> n;
    cout << fun(n);
}

/*
#include <iostream>
using namespace std;

typedef long long long_t;

long_t fun(long_t n) {
    long_t i, j, cnt = 0;
    for (i = 1; i <= 4 * n; i += 2)
        for (j = n; j >= 1; j--)
            cnt++;
    return cnt;
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}
*/
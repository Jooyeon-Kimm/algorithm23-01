/*
Input: 1 2 4
Output: 15

Input: 4 8 16
Output: 70

Input: 1024 2048 4096
Output: 99840

*/

#include <iostream>
#include <cmath>
using namespace std;

typedef long long longType;

longType logB(longType x, longType base) {
    return log(x) / log(base);
}

longType fun(longType n, longType m, longType p) {
    longType cnt = 0;
    cnt = (logB(4 * p, 2) + 1) * (logB(2 * m, 2) + 1) * ceil((float)n / 2);

    return cnt;
}

int main() {
    longType n, m, p;
    cin >> n >> m >> p;
    cout << fun(n, m, p);
}

/*
#include <iostream>
using namespace std;

typedef long long long_t;

long_t fun(long_t n, long_t m, long_t p) {
    long_t i, j, k, cnt = 0;
    for (i = 1; i <= 2 * n; i += 4)
        for (j = 1; j <= 2 * m; j *= 2)
            for (k = 4 * p; k >= 1; k /= 2)
                cnt++;
    return cnt;
}

int main() {
    long_t n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    printf("%lld", fun(n, m, p));
}


*/
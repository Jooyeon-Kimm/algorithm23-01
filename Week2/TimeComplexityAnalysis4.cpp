#include <iostream>
#include <cmath>
using namespace std;

typedef long long longType;

longType logB(longType x, longType base) {
    return log(x) / log(base);
}

longType fun(longType n) {
    double answer = pow(8, logB(n, 4) + 1);
    return (longType)answer;
}

int main() {
    longType n;
    cin >> n;
    cout << fun(n);
}

/*
#include <iostream>
using namespace std;

typedef long long longType;

longType fun(longType n) {
    if (n == 0)
        return 1;
    else {
        longType s = 0;
        for (int i = 1; i <= 8; i++)
            s += fun(n / 4);
        return s;
    }
}

int main() {
    longType n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}
*/
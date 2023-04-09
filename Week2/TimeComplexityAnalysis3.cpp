#include <iostream>
#include <cmath>
using namespace std;

typedef long long longType;

longType logB(longType x, longType base) {
    return log(x) / log(base);
}

longType fun(longType n) {
    double answer = pow(4, logB(n, 2) + 1);
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
    else
        return fun(n / 2) + fun(n / 2) + fun(n / 2) + fun(n / 2);
}

int main() {
    longType n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}
*/
/*
Considering the max value of integer,
I define Fibonacci function:
F(n) = (F(n-1) + F(n-2)) % 1000000

Input:
100

Output:
915075


Input:
1000

Output:
228875

*/
#include <vector>
using namespace std;

int fib(int n) {

    if (n < 2) return n;

    int pp = 0, p = 1, result;
    for (int i = 0; i < n - 1; i++) {
        result = (pp + p) % 1000000;
        pp = p;
        p = result;
    }

    return result;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", fib(n));
    
    return 0;
}
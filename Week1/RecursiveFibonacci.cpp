/*
Considering the max value of integer,
I define Fibonacci function:
F(n) = (F(n-1) + F(n-2)) % 1000000

Input:
2

Output:
1
3
*/
#include <vector>
using namespace std;

int call = 0; // 피보나치 재귀함수 호출 횟수

int fib(int n) {
	call++;

	if (n == 0 || n == 1) return n;
	return (fib(n - 1) + fib(n - 2)) % 1000000;
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", fib(n));
	printf("%d", call);

}
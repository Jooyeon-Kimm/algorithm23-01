
#include <iostream>

using namespace std;

void printCollatz(long long N) {
    while (true) {

        if (N == 1) {
            cout << N;
            break;
        }

        cout << N << " ";
        N = (N % 2 == 0) ? (N / 2) : ((N * 3) + 1);

    }

}

long long lengCollatz(long long N) {
    long long cnt = 0;

    while (true) {
        if (N == 1)
            break;

        N = (N % 2 == 0) ? (N / 2) : ((N * 3) + 1);
        cnt++;
    }

    return cnt;
}

int main() {
    long long a, b;
    long long maxNum = 0, maxLength = 0; // 가장 긴 수, 길이

    cin >> a >> b;

    for (int i = a; i <= b; i++) {
        long long temp = lengCollatz(i);
        if (temp >= maxLength) {
            maxNum = i;
            maxLength = temp;
        }

    }
    cout << maxNum << " " << maxLength;
    printCollatz(maxNum);

    return 0;

}
#include <iostream>
using namespace std;

int callCnt = 1;
int moveCnt = 0;

void hanoi(int n, int K, char src, char via, char dst) {
    if (n == 1) {
        moveCnt++;
        if (moveCnt == K)
            cout << src << "->" << dst << endl;
    }
    else {
        hanoi(n - 1, K, src, dst, via); 
        callCnt++;

        hanoi(1, K, src, via, dst); 
        callCnt++;

        hanoi(n - 1, K, via, src, dst); 
        callCnt++;
    }
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    hanoi(n, k, 'A', 'B', 'C');
    cout << callCnt;
}

/*
#include <iostream>
using namespace std;

void hanoi(int n, char src, char via, char dst) {
    if (n == 1) {
        printf("%c -> %c\n", src, dst);
    }
    else {
        hanoi(n - 1, src, dst, via);
        hanoi(1, src, via, dst);
        hanoi(n - 1, via, src, dst);
    }
}

int main() {
    int n;
    cin >> n;
    hanoi(n, 'A', 'B', 'C');
}
*/
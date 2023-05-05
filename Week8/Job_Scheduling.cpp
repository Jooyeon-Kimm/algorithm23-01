#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef vector<int> v1;

// 가능한지 확인
bool is_feasible(v1& K, v1& deadline) {
    for (int i = 1; i < K.size(); i++)
        if (i > deadline[K[i]])
            return false;
    return true;
}

void schedule(int n, v1& deadline, v1& profit, v1& J) {
    J.clear();
    if(1 <= deadline[1])
        J.push_back(1);
    
    for (int i = 1; i <= n; i++) {
        v1 K = J;

        int idx = 0;
        for (int k = K.size() - 1; k > 0; k--) {
            if (deadline[K[k]] <= deadline[i]) {
                idx = k;
                break;
            }
        }

        K.insert(K.begin() + idx + 1, i);

        bool feasible = is_feasible(K, deadline);
        if (feasible) J = K;
    }
   
}

void input(int& n, v1& deadline, v1& profit) {
    for (int i = 1; i <= n; i++) {
        cin >> deadline[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> profit[i];
    }
}

void output(v1& J, v1& profit) {
    int total_profit = 0;
    for (int i = 1; i < J.size(); i++) {
        total_profit += profit[J[i]];
    }
    cout <<total_profit << endl;

    for (int i = 1; i < J.size(); i++) {
        cout << profit[J[i]];
        if (i == J.size() - 1) break;
        else cout << " ";
    }
}

void jobScheduling() {
    // 변수 선언과 입력
    int n;
    cin >> n;
    v1 deadline(n + 1), profit(n + 1), J;
    input(n, deadline, profit);

    // 데드라인 스케쥴링
    schedule(n, deadline, profit, J);

    // 결과 출력
    output(J, profit);
}

int main() {
    jobScheduling();
    return 0;
}

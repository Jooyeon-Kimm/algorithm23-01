/*
직접 구현한 함수
print(), ctoi()
나머지는 강의자료
*/

#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> LargeInteger;
int threshold;
int cnt = 0; // prod 호출 횟수

// 올림 계산
void roundup_carry(LargeInteger& v) {
    int carry = 0;

    for (int i = 0; i < v.size(); i++) 
    {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] = v[i] % 10;
    }

    if (carry != 0)
        v.push_back(carry);
}

// 맨 앞 0 제거
void remove_leading_zeros(LargeInteger& v) {
    while (v.size() != 0 && v.back() == 0)
        v.pop_back();
}

// char to integer
int ctoi(char c) {
    return c - '0';
}

void ladd(LargeInteger a, LargeInteger b, LargeInteger& c) 
{
    c.resize(max(a.size(), b.size()));

    // c 처음부터 끝까지 0 할당
    fill(c.begin(), c.end(), 0);

    for (int i = 0; i < c.size(); i++) 
    {
        if (i < a.size()) 
            c[i] += a[i];

        if (i < b.size()) 
            c[i] += b[i];
    }
    roundup_carry(c);
}

// 곱셈
void lmult(LargeInteger a, LargeInteger b, LargeInteger& c) {
    c.resize(a.size() + b.size() - 1);

    fill(c.begin(), c.end(), 0);

    for (int i = 0; i < a.size(); i++)
        for (int k = 0; k < b.size(); k++)
            c[i + k] += a[i] * b[k];

    roundup_carry(c);
}

void pow_by_exp(LargeInteger u, int m, LargeInteger& v) {
    if (u.size() == 0)
        v.resize(0);

    else {
        v.resize(u.size() + m);
        fill(v.begin(), v.end(), 0);
        copy(u.begin(), u.end(), v.begin() + m);
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger& v) {
    if (u.size() == 0)
        v.resize(0);

    else {
        // Note that u.size() can be smaller than m.
        int k = m < u.size() ? m : u.size();
        v.resize(k);
        copy(u.begin(), u.begin() + k, v.begin());
        remove_leading_zeros(v);
    }
}

void div_by_exp(LargeInteger& a, int exp, LargeInteger& c) {
    for (int i = exp; i < a.size(); i++)
        c.push_back(a[i]);
}

void prod(LargeInteger u, LargeInteger v, LargeInteger& r) {
    cnt++;

    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;

    int n = max(u.size(), v.size());

    if (u.size() == 0 || v.size() == 0)
        r.resize(0);

    else if (n <= threshold)
        lmult(u, v, r);

    else {
        int m = n / 2;
        div_by_exp(u, m, x); 
        rem_by_exp(u, m, y);
        div_by_exp(v, m, w); 
        rem_by_exp(v, m, z);
        // t2 <- prod(x,w) * 10^(2*m)

        prod(x, w, t1); 
        pow_by_exp(t1, 2 * m, t2);

        // t6 <- (prod(x,z)+prod(w,y)) * 10^m
        prod(x, z, t3); 
        prod(w, y, t4); 
        ladd(t3, t4, t5); 
        pow_by_exp(t5, m, t6);

        // r <- t2 + t6 + prod(y, z)
        prod(y, z, t7); 
        ladd(t2, t6, t8); 
        ladd(t8, t7, r);
    }
}

// LargeInteger 한 문자씩 거꾸로 출력
void print(LargeInteger& v)
{
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << v[i];
    }
}

int main(void) {
    LargeInteger A, B, C;
    string sA, sB;

    cin >> threshold;
    cin >> sA >> sB; 
    // LargeInteger형을 입력받을 수 없으므로
    // string으로 입력받기

    for (int i = sA.length() - 1; i >= 0; i--) 
        A.push_back(ctoi(sA[i]));

    for (int i = sB.length() - 1; i >= 0; i--) 
        B.push_back(ctoi(sB[i]));

    // 카리츠바 큰 수의 곱셈
    prod(A, B, C);

    // prod() 호출 횟수 출력
    cout << cnt << "\n";

    // 곱셈 결과 출력
    print(C);
    return 0;


   
}


#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10, BASE = 10000;
int a[10000], b[10000], c[10000], f[10000], T;

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

void Print(int a[]) {
    printf("%d", a[a[0]]);
    for (int i = a[0] - 1; i >= 1; --i) {
        printf("%04d", a[i]);
    }
    printf("\n");
}

void Init(int a[]) {
    string s;
    cin >> s;
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        int j = (len - i + 3) / 4;
        a[j] = a[j] * 10 + s[i] - '0';
    }
    
    a[0] = (len + 3) / 4;
}

int Comp(int a[], int b[]) {
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    for (int i = a[0]; i >= 1; --i) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}

void DivLow(int a[], int k) {
    int t = 0;
    for (int i = a[0]; i >= 1; --i) {
        t = t * BASE + a[i];
        a[i] = t / k;
        t %= k;
    }
    
    while (a[a[0]] == 0 && a[0] > 0) a[0]--;
}

void Minus(int a[], int b[]) {
    for (int i = 1; i <= a[0]; ++i) {
        a[i] -= b[i];
        if (a[i] < 0) {
            a[i + 1]--;
            a[i] += BASE;
        }
    }
    while (a[a[0]] == 0 && a[0] > 0) a[0]--;
}

void Gcd(int a[], int b[], int t) {
    if (Comp(a, b) == 0) {
        T = t; 
        return;
    }
    if (Comp(a, b) == -1) {
        Gcd(b, a, t);
        return;
    }
    
    int ta, tb;
    if (a[1] % 2 == 0) {
        DivLow(a, 2);
        ta = 1;
    } else ta = 0;
    
    if (b[1] % 2 == 0) {
        DivLow(b, 2);
        tb = 1;
    } else tb = 0;
    
    if (!ta && !tb) {
        Minus(a, b);
        Gcd(a, b, t);
    } else if (ta && tb) {
        Gcd(a, b, t + 1);
    } else Gcd(a, b, t);
}

void MulLow(int a[], int k) {
    int t = 0;
    for (int i = 1; i <= a[0]; ++i) {
        a[i] *= k;
        a[i + 1] += a[i] / BASE;
        a[i] %= BASE;
    }
    
    while (a[a[0] + 1] > 0) {
        a[0]++;
        a[a[0] + 1] += a[a[0]] / BASE;
        a[a[0]] %= BASE;
    }
}

void MulHigh(int a[], int b[]) {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= a[0]; ++i) {
        for (int j = 1; j <= b[0]; ++j) {
            c[i + j - 1] += a[i] * b[j];
            c[i + j] += c[i + j - 1] / BASE;
            c[i + j - 1] %= BASE;
        }
    }
    
    c[0] = a[0] + b[0];
    while (c[c[0]] == 0 && c[0] > 0) c[0]--;
    
    for (int i = 0; i <= c[0]; ++i) {
        a[i] = c[i];
    }
}

int main() {
    Init(a);
    Init(b);
    
    Gcd(a, b, 0);
    
    if (T == 0) Print(a);
    else {
        f[0] = f[1] = 1;
        for (int i = 1; i <= T; ++i) {
            MulLow(f, 2);
        }
        MulHigh(f, a);
        Print(f);
    }
}
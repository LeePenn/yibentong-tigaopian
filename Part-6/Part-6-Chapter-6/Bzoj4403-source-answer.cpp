#include <bits/stdc++.h>
using namespace std;
#define ll long long

//static char *p1, *p2, buf[100000];
//#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
template<typename T>
inline void read(T &x) {
    //T flag = 1;   //可选
    x = 0;
    char ch = getchar();

    while (!isdigit(ch))
        ch = getchar();    //可选

    //while (!isdigit(ch)) {if (ch == '-')flag = -1; ch = getchar();}   //可选
    while (isdigit(ch)) {
        x = x * 10 + ch - '0', ch = getchar();
    }

    //x *= flag;    //可选
    return;
}
template<typename T>
inline void write(T x) {
    //if (x < 0) putchar('-'), x = -x;  //可选
    if (x > 9) {
        write(x / 10);
    }

    putchar(x % 10 + '0');
}

const int base = 1000003;
const int MAXN = 1000010;

int f[MAXN], g[MAXN];

int qpow(int a, int n) {
    int ans = 1;

    while (n) {
        if (n & 1)
            ans = (ll)ans * a % base;

        a = (ll)a * a % base;
        n >>= 1;
    }

    return ans;
}

void init() {
    f[0] = g[0] = 1;

    for (int i = 1; i < MAXN; i++) {
        f[i] = (ll)f[i - 1] * i % base;
        g[i] = (ll)g[i - 1] * qpow(i, base - 2) % base;
    }

    return;
}

int C(int n, int m) {
    if (n < m)
        return 0;

    return (ll)f[n] * g[m] * g[n - m] % base;
}

int lucas(int n, int m) {
    if (m == 0)
        return 1;
    else
        return (ll)lucas(n / base, m / base) * C(n % base, m % base) % base;
}

int T, L, R, N;

int main() {
    //freopen("4455.4.in", "r", stdin);
    init();
    read(T);

    while (T--) {
        read(N);
        read(L);
        read(R);
        write((lucas(R - L + 1 + N, N) - 1 + base) % base);
        //要输出正值
        putchar('\n');
    }

    return 0;
}
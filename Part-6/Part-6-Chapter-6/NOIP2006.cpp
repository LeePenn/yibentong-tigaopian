#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int total[301];

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

int Gcd(int a, int b) {
    if (!b) return a;
    return Gcd(b, a % b);
}

void CC(int n, int m) {
    if (n < m) return;
    
    int a[301], b[301], i, j, x;
    for (i = m; i >= 1; --i) {
        a[i] = n + i - m;
        b[i] = i;
    }
    
    for (i = 1; i <= m; ++i) {
        if (b[i] == 1) continue;
        for (j = m; j >= 1; --j) {
            x = Gcd(b[i], a[j]);
            b[i] /= x;
            a[j] /= x;
            if (b[i] == 1) break;
        }
    }
    // b一定能约掉
    memset(b, 0, sizeof(b));
    b[1] = 1; b[0] = 1;
    int g = 0;
    for (j = 1; j <= m; ++j) {
        g = 0;
        if (a[j] == 1) continue;
        for (i = 1; i <= b[0]; ++i) {
            b[i] = b[i] * a[j] + g;
            g = b[i] / 10;
            b[i] %= 10;
            if (i == b[0] && g != 0) b[0]++;
        }
    }
    
    total[0] = max(total[0], b[0]);
    for (i = 1; i <= total[0]; ++i) {
        total[i] += b[i];
        total[i + 1] += total[i] / 10;
        total[i] %= 10;
    }
    
    if (total[total[0] + 1] != 0) total[0]++;
}

int main() {
    int k, w, n, m, c, i;
    memset(total, 0, sizeof(total));
    cin >> k >> w;
    n = (1 << k) - 1;
    m = w / k;
    c = w % k;
    for (i = m; i >= 2; --i) CC(n, i);
    c = (1 << c) - 1;
    if (c >= 1 && n > m) {
        for (i = 1; i <= c; ++i) CC(n - i, m);
    }
    for (int j = total[0]; j >= 1; --j) cout << total[j];
    
    return 0;
}


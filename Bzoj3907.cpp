#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
int n, m;
int a[N], b[N];
int ans1[N], ans2[N], ans[N];

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
    return !b ? a : Gcd(b, a % b);
}

void Print(int a[]) {
    for (int i = a[0]; i >= 1; --i) 
        printf("%d", a[i]);
        
    printf("\n");
}

void C(int n, int m, bool t) {
    for (int i = 1; i <= m; ++i) {
        a[i] = n - m + i;
        b[i] = i;
    }
    
    for (int i = 1; i <= m; ++i) {
        if (b[i] == 1) continue;
        for (int j = 1; j <= n; ++j) {
            int x = Gcd(b[i], a[j]);
            a[j] /= x;
            b[i] /= x;
            if (b[i] == 1) break;
        }
    }
    
    memset(b, 0, sizeof(b));
    b[0] = b[1] = 1;
    int g = 0;
    for (int i = 1; i <= m; ++i) {
        g = 0;
        for (int j = 1; j <= b[0]; ++j) {
            b[j] = b[j] * a[i] + g;
            g = b[j] / 10;
            b[j] %= 10;
        }
        while (g) {
            b[0]++;
            b[b[0]] = g % 10;
            g /= 10;
        }
    }
    
    if (t) {
        memcpy(ans1, b, sizeof(ans1));
    } else {
        memcpy(ans2, b, sizeof(ans2));
    }
    
}

void Sub(int a[], int b[]) {
    for (int i = 1; i <= a[0]; ++i) {
        if (a[i] < b[i]) {
            a[i + 1]--;
            a[i] += 10;
        }
        a[i] -= b[i];
    }
    
    while (a[a[0]] == 0 && a[0] > 1) {
        a[0]--;
    }
    
    memcpy(ans, a, sizeof(ans));
}

int main() {
    cin >> n >> m;
    C(n + m, m, true);
    C(n + m, m - 1, false);
    Sub(ans1, ans2);
    
    Print(ans);
    
    return 0;
}


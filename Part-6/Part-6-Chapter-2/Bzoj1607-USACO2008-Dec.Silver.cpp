#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int n, m, a[N], num[N];
int ans[N];

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

void Read() {
    n = ReadInt();
    for (int i = 1; i <= n; ++i) {
        a[i] = ReadInt();
        num[a[i]]++;
        m = max(m, a[i]);
    }
}

void Work() {
    for (int i = 1; i <= m; ++i) {
        if (num[i]) {
            for (int j = 1; j * i <= m; ++j) {
                ans[j * i] += num[i];
            }
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", ans[a[i]] - 1);
    }
}

int main() {
    Read();
    
    Work();

    return 0;
}
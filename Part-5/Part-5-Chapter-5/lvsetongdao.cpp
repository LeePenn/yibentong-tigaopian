#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 10;
int n, t;
int a[N], f[N], q[N];

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

void Read() {
    cin >> n >> t;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}

bool DP(int m) {
    int hh = 1, tt = 1;
    memset(q, 0, sizeof(q));
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    int ans = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        while (hh <= tt && q[hh] < i - m - 1) hh++;
        f[i] = f[q[hh]] + a[i];
        while (hh <= tt && f[q[tt]] > f[i]) tt--;
        q[++tt] = i;
        if (i >= n - m) ans = min(ans, f[i]);
        // printf("@@ i = %d f[i] = %d\n", i, f[i]);
    }
    // printf("## m = %d ans = %d\n", m, ans);
    
    return ans <= t;
}

// 逆向思维，空题长度不知道的情况下，很难建模，但是如果知道了，就可以套用模型
void Work() {
    int l = 0, r = n;
    int ans = n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (DP(mid)) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    
    printf("%d\n", ans);
}

int main() {
    Read();
    
    Work();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL a[N], s[N], d[N], q[N], g[N], f[110][N];
int n, m, p;

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
    cin >> n >> m >> p;
    int j;
    for (int i = 2; i <= n; ++i) {
        cin >> j;
        d[i] = d[i - 1] + j;
    }
    
    int k;
    for (int i = 1; i <= m; ++i) {
        cin >> j >> k;
        a[i] = k - d[j];
    }
}

void DP() {
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i) {
        s[i] = s[i - 1] + a[i];
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    int hh, tt;
    for (int i = 1; i <= p; ++i) {
        for (int j = 1; j <= m; ++j) g[j] = f[i - 1][j] + s[j];
        hh = 1, tt = 1;
        q[1] = 0;
        for (int j = 1; j <= m; ++j) {
            while (hh < tt && g[q[hh + 1]] - g[q[hh]] < a[j] * (q[hh + 1] - q[hh])) hh++;
            
            f[i][j] = min(f[i - 1][j], g[q[hh]] + a[j] * (j - q[hh]) - s[j]);
            
            if (g[j] >= 0x3f3f3f3f3f3f3f3fll) continue;
            
            while (hh < tt && (g[j] - g[q[tt]]) * (q[tt] - q[tt - 1]) <= (g[q[tt]] - g[q[tt - 1]]) * 
            (j - q[tt])) tt--;
            
            q[++tt] = j;
        }
    }
    
    cout << f[p][m] << endl;
}

int main() {
    Read();
    
    DP();

    return 0;
}
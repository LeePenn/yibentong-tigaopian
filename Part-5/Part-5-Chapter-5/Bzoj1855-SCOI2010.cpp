#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 4000 + 5;
int n, MP, m;
int q[N], AP[N], BP[N], AS[N], BS[N];
int f[N][N], val[N];

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
    cin >> n >> MP >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> AP[i] >> BP[i] >> AS[i] >> BS[i];
    }
}

void DP() {
    memset(f, -0x3f3f3f3f, sizeof(f));
    f[0][0] = 0;
    // printf("%d\n", f[1][1]);
    // 持有x股的最大价值
    memset(val, -0x3f3f3f3f, sizeof(val));
    val[0] = 0;
    int hh, tt;
    for (int i = 1; i <= n; ++i) {
        hh = 1, tt = 0;
        // buy
        for (int j = 0; j <= MP; ++j) {
            // j - AS[i] 到 j这段连续区间内，考虑增加AP[i]后的最大价值，思路类似男人八题中的Coins思考
            while (hh <= tt && q[hh] < j - AS[i]) hh++;
            while (hh <= tt && val[q[tt]] - (j - q[tt]) * AP[i] < val[j]) tt--;
            q[++tt] = j;
            f[i][j] = max(f[i][j], val[q[hh]] - (j - q[hh]) * AP[i]);
        }
        
        hh = 1, tt = 0;
        // sell
        for (int j = MP; j >= 0; --j) {
            while (hh <= tt && q[hh] > j + BS[i]) hh++;
            while (hh <= tt && val[q[tt]] + (q[tt] - j) * BP[i] < val[j]) tt--;
            q[++tt] = j;
            f[i][j] = max(f[i][j], val[q[hh]] + (q[hh] - j) * BP[i]);
        }
        
        if (i > m) {
            for (int j = 0; j <= MP; ++j) {
                val[j] = max(val[j], f[i - m][j]);
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans = max(ans, f[i][0]);
    }
    
    printf("%d\n", ans);
}

int main() {
    Read();
    
    DP();    
    return 0;
}
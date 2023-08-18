#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10;
int n, b[N], c[N], k;
int val[N], f[N], q[N];

int ReadInt() {
    int r = 0, f = 1;
    
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
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
    for (int i = 1; i <= n; ++i) b[i] = ReadInt();
    for (int i = 1; i <= n; ++i) c[i] = ReadInt();
    k = ReadInt();
}

void DP() {
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    
    int hh, tt;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < b[i]; ++j) {
            // 队列每次都会重置，这里加上memset(v, 0, sizeof(v))结果不变
            hh = 1, tt = 0;
            for (int m = 0; m * b[i] + j <= k; ++m) {
                // 价值为 k * a[i] + j的最小硬币，因为要增加m枚b[i]价值硬币，所以减去m枚b[i]的价值
                val[m * b[i] + j] = f[m * b[i] + j] - m;
                // 这部分推荐画图理解，以j = 0为例，配合求区间最值的例题理解
                while (hh <= tt && m - q[hh] > c[i]) hh++;
                while (hh <= tt && val[q[tt] * b[i] + j] >= val[m * b[i] + j]) tt--;
                q[++tt] = m;
                // val的值都是没有加上当前硬币的效果
                f[m * b[i] + j] = val[q[hh] * b[i] + j] + m;
            }
        }
    }
    // 这里要注意，这里题目是保证有解的，如果无解，输出应该是个大于0x3f的值
    printf("%d\n", f[k]);
}

int main() {
    Read();
    
    DP();

    return 0;
}
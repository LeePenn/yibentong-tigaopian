#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000 + 5;
int a, b, n, m[N][N];
int q[N], Fmax[N][N], Fmin[N][N], Frmax[N][N], Frmin[N][N];

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
    cin >> a >> b >> n;
    for (int i = 1; i <= a; ++i) {
        for (int j = 1; j <= b; ++j) 
            cin >> m[i][j];
    }
}

void Init() {
    int hh, tt;
    for (int j = 1; j <= b; ++j) {
        hh = 1, tt = 0;
        for (int i = 1; i <= a; ++i) {
            while (hh <= tt && q[hh] <= i - n) hh++;
            while (hh <= tt && m[q[tt]][j] < m[i][j]) tt--;
            q[++tt] = i;
            Fmax[j][i] = m[q[hh]][j];
        }
        
        hh = 1, tt = 0;
        for (int i = 1; i <= a; ++i) {
            while (hh <= tt && q[hh] <= i - n) hh++;
            while (hh <= tt && m[q[tt]][j] > m[i][j]) tt--;
            q[++tt] = i;
            Fmin[j][i] = m[q[hh]][j];
        }
    }
}

void Test() {
    for (int j = 1; j <= b; ++j) {
        for (int i = 1; i <= a; ++i) {
            printf("max = %d, min = %d\n", Fmax[j][i], Fmin[j][i]);
        }
        printf("\n");
    }
    
}

void Work() {
    int ans = 0x7fffffff;
    int hh, tt;
    for (int i = n; i <= a; ++i) {
        hh = 1, tt = 0;
        for (int j = 1; j <= b; ++j) {
            while (hh <= tt && q[hh] <= j - n) hh++;
            while (hh <= tt && Fmax[q[tt]][i] < Fmax[j][i]) tt--;
            q[++tt] = j;
            Frmax[i][j] = Fmax[q[hh]][i];
            // printf("!! i = %d, %d\n", i, Frmax[i][j]);
        }
        
        hh = 1, tt = 0;
        for (int j = 1; j <= b; ++j) {
            while (hh <= tt && q[hh] <= j - n) hh++;
            while (hh <= tt && Fmin[q[tt]][i] > Fmin[j][i]) tt--;
            q[++tt] = j;
            Frmin[i][j] = Fmin[q[hh]][i];
            if (j >= n) ans = min(ans, Frmax[i][j] - Frmin[i][j]);
            // printf("@@ i = %d, %d\n", i, Frmin[i][j]);
        }
    }
    
    printf("%d\n", ans);
}

int main() {
    Read();
    
    Init();
    
    Work();
    
    return 0;
}
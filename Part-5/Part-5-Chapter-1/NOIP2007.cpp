#include <bits/stdc++.h>
using namespace std;
const int N = 80 + 5, BASE = 10;
int n, m;
int a[N][N];
int Exp2[N][N], s1[N], s2[N], s3[N], s4[N];
int f[N][N][80];
int ans[80], tmpAns[80];

void Read() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
}

void Mul(int c1[], int num, int c2[]) {
    c2[0] = c1[0];
    for (int i = 1; i <= c1[0]; ++i) {
        c2[i + 1] += c1[i] * num / BASE;
        c2[i] += (c1[i] * num) % BASE;
    }
    
    while (c2[c2[0] + 1]) {
        ++c2[0];
        c2[c2[0]] += c2[c2[0] - 1] / BASE;
        c2[c2[0] - 1] %= BASE;
    }
}

void Mul2(int c1[], int c2[], int c3[]) {
    for (int i = 1; i <= c1[0]; ++i) {
        int x = 0;
        for (int j = 1; j <= c2[0]; j++) {
            c3[i + j - 1] = c3[i + j - 1] + (c1[i] * c2[j] + x) % BASE;
            x = c3[i + j - 1] / BASE;
            c3[i + j - 1] %= BASE;
        }
        c3[i + c2[0]] = x;
    }
    
    int len = c1[0] + c2[0];
    while (c3[len] == 0 && len > 1) {
        len--;
    }
    c3[0] = len;
}

void Add(int c1[], int c2[], int c3[]) {
    int len = max(c1[0], c2[0]);
    int x = 0;
    for (int i = 1; i <= len; ++i) {
        c3[i] = c3[i] + c1[i] + c2[i] + x;
        x = c3[i] / BASE;
        c3[i] %= BASE;
    }
    c3[len + 1] = x;
    c3[0] = len + 1;
    while (c3[c3[0]] == 0 && c3[0] > 1) {
        c3[0]--;
    }
}

bool Compare(int c1[], int c2[]) {
    if (c1[0] > c2[0]) return true;
    if (c1[0] < c2[0]) return false;
    for (int i = c1[0]; i >= 1; --i) {
        if (c1[i] > c2[i]) return true;
        if (c1[i] < c2[i]) return false;
    }
    return false;
}

void Print(int c[]) {
    for (int i = c[0]; i >= 1; --i) {
        printf("%d", c[i]);
    }
    printf("\n");
}

void DP(int row) {
    memset(f, 0, sizeof(f));
    for (int L = 1; L <= m; ++L) {
        for (int i = 1; i + L - 1 <= m; ++i) {
            int j = i + L - 1;
            int lev = m - L + 1;
            if (i == j) {
                Mul(Exp2[lev], a[row][i], f[i][j]);
                // printf("## %d %d\n", i, j);
                // Print(f[i][j]);
                continue;
            }
            
            memset(s1, 0, sizeof(s1));
            memset(s2, 0, sizeof(s2));
            Mul(Exp2[lev], a[row][i], s1);
            Add(s1, f[i + 1][j], s2);
            // printf("!!!\n");
            // Print(s2);
            
            memset(s3, 0, sizeof(s3));
            memset(s4, 0, sizeof(s4));
            Mul(Exp2[lev], a[row][j], s3);
            Add(s3, f[i][j - 1], s4);
            // printf("!!!\n");
            // Print(s4);
            
            if (Compare(s2, s4)) {
                memcpy(f[i][j], s2, sizeof(s2));
            } else {
                memcpy(f[i][j], s4, sizeof(s4));
            }
            // printf("## %d %d\n", i, j);
            // Print(f[i][j]);
        }
    }
    
    // printf("$$$$$$$\n");
    // Print(f[1][m]);
    memset(tmpAns, 0, sizeof(tmpAns));
    tmpAns[0] = 1, tmpAns[1] = 0;
    Add(ans, f[1][m], tmpAns);
    memcpy(ans, tmpAns, sizeof(tmpAns));
}


void init() {
    memset(Exp2, 0, sizeof(Exp2));
    Exp2[0][0] = Exp2[0][1] = 1;
    for (int i = 1; i <= 80; ++i) {
        Mul(Exp2[i - 1], 2, Exp2[i]);
    }
    ans[0] = 1, ans[1] = 0;
}

void Work() {
    init();
    
    for (int i = 1; i <= n; ++i) {
        DP(i);
    }
    
    Print(ans);
}

int main() {
    Read();
    Work();

    return 0;
}

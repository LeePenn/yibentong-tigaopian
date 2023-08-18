#include <bits/stdc++.h>
using namespace std;
// m = 10, row not conflict num is 60
const int N = 100 + 3, M = 60 + 4;
int n, m;
char ch[N];
int g[N];
int state[M], cnt;
int num[M];
int f[N][M][M];

void Read() {
    cin >> n >> m;
    string line;
    getline(cin, line);
    int x;
    for (int i = 1; i <= n; ++i) {
        scanf("%s\n", ch + 1);
        x = 0;
        for (int j = 1; j <= m; ++j) {
            if (ch[j] == 'P') {
                x += (1 << (m - j));
            }
        }
        g[i] = x;
    }
}

int get_num(int x) {
    int res = 0;
    while (x) {
        x -= x & (-x);
        res++;
    }
    return res;
}

void Init() {
    for (int i = 0; i < (1 << m); ++i) {
        // row not conflict
        if ((i & (i << 1)) || (i & (i << 2)) || (i & (i >> 1)) || (i & (i >> 2))) continue;
        state[++cnt] = i;
        num[cnt] = get_num(i);
    }
}

void DP() {
    for (int i = 1; i <= cnt; ++i) {
        if ((state[i] & g[1]) != state[i]) continue;
        
        f[1][i][0] = num[i];
    }   

    for (int i = 1; i <= cnt; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            if ((state[i] & g[2]) != state[i] || (state[j] & g[1]) != state[j] || 
            (state[i] & state[j])) {
                continue;
            }   
            f[2][i][j] = max(f[2][i][j], f[1][j][0] + num[i]);
        }
    }
    
    // int t = 0;
    // for (int i = 1; i <= cnt; ++i) {
    //     for (int j = 1; j <= cnt; ++j) {
    //         t = max(t, f[2][state[i]][state[j]]);
    //     }
    // }
    
    // printf("%d\n", t);
    // return;
    
    for (int i = 3; i <= n; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            if ((state[j] & g[i]) != state[j]) continue;
            
            for (int k = 1; k <= cnt; ++k) {
                if ((state[j] & state[k]) || (state[k] & g[i - 1]) != state[k]) continue;
                
                for (int kk = 1; kk <= cnt; ++kk) {
                    if ((state[k] & state[kk]) || (state[kk] & state[j]) || 
                    (state[kk] & g[i - 2]) != state[kk]) continue;
                    
                    f[i][j][k] = max(f[i][j][k], f[i - 1][k][kk] + num[j]);
                }
            }
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) {
        for (int j = 1; j <= cnt; ++j) {
            ans = max(ans, f[n][i][j]);
        }
    }
    
    printf("%d\n", ans);
}

int main() {
    Read();
    
    Init();
    
    DP();


    return 0;
}
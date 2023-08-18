#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 62, L = 100, Z = 26, P = 10007;
int n, m;
int ch[N * L][Z], tot = 1;
bool b[N * L];
string s[N];
int nxt[N * L];
int dp[L][N * L];

void build_trie(int id) {
    int u = 1, len = s[id].length();
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'A';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    b[u] = true;
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < Z; i++) {
        ch[0][i] = 1;
    }
    nxt[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < Z; i++) {
            if (!ch[u][i]) ch[u][i] = ch[nxt[u]][i];
            else {
                nxt[ch[u][i]] = ch[nxt[u]][i];
                b[ch[u][i]] |= b[nxt[ch[u][i]]];
                q.push(ch[u][i]);
                
            }
        }
    }
    
}

LL ksm(int a, int b) {
    LL ans = 1;
    while (b) {
        if (b & 1) {
            ans *= a;
            ans %= P;
        }
        a *= a;
        a %= P;
        b >>= 1;
    }
    return ans;
}

void work() {
    dp[0][1] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= tot; j++) {
            for (int k = 0; k < Z; k++) {
                if (!b[ch[j][k]]) {
                    dp[i][ch[j][k]] += dp[i - 1][j];
                    dp[i][ch[j][k]] %= P;
                }
            }
        }
    }
    
    LL sum = 0;
    for (int j = 1; j <= tot; j++) {
        sum += dp[m][j];
        sum %= P;
    }
    
    printf("%lld\n", (ksm(26, m) + P - sum) % P);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        build_trie(i);
    }
    bfs();
    work();
    
    
    

    return 0;
}
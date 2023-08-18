#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10, M = 1e6 + 10, Z = 26;
int ch[N * 50][Z], tot = 1;
int b[N * 50], nxt[N * 50];
int kase, n;
string s1, s2;
int que[N * 50];

void build_trie() {
    int u = 1, len = s1.length(); 
    for (int i = 0; i < len; i++) {
        int c = s1[i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    b[u]++;
}

void bfs() {
    for (int i = 0; i < Z; i++) {
        ch[0][i] = 1;
    }
    int q1 = 1, q2 = 1;
    que[1] = 1, nxt[1] = 0;
    while (q1 <= q2) {
        int u = que[q1++];
        for (int i = 0; i < Z; i++) {
            if (!ch[u][i]) ch[u][i] = ch[nxt[u]][i];
            else {
                que[++q2] = ch[u][i];
                int v = nxt[u];
                while (v && !ch[v][i]) v = nxt[v];
                // 孩子节点的nxt = 父节点的前缀节点对应的子节点
                nxt[ch[u][i]] = ch[v][i];
            }
        }
    }
}

void find() {
    int u = 1, k = 1, len = s2.length(), ans = 0;
    for (int i = 0; i < len; i++) {
        int c = s2[i] - 'a';
        k = ch[u][c];
        while (k > 1) {
            ans += b[k];
            b[k] = 0;
            k = nxt[k];
        }
        u = ch[u][c];
    }
    
    printf("%d\n", ans);
}

int main() {
    cin >> kase;
    while (kase--) {
        cin >> n;
        memset(ch, 0, sizeof(ch));
        memset(b, 0, sizeof(b));
        memset(nxt, 0, sizeof(nxt));
        for (int i = 1; i <= n; i++) {
            cin >> s1;
            build_trie();
        }
        bfs();
        cin >> s2;
        find();
    }
    
    return 0;
}
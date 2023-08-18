#include <bits/stdc++.h>
using namespace std;

const int N = 210, L = 1e6 + 10, Z = 26;
int n;
int ch[L][Z], tot = 1;
char s[N][L];
int idx[L], cnt[L];
int que[L], q1, q2, nxt[L];

void build_trie(int id) {
    int u = 1, len = strlen(s[id]);
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    idx[u] = id;
}

void bfs() {
    for (int i = 0; i < Z; i++) {
        ch[0][i] = 1;
    }
    que[1] = 1, q1 = 1, q2 = 1, nxt[1] = 0;
    while (q1 <= q2) {
        int u = que[q1++];
        for (int i = 0; i < Z; i++) {
            if (!ch[u][i]) ch[u][i] = ch[nxt[u]][i];
            else {
                que[++q2] = ch[u][i];
                int v = nxt[u];
                while (v && !ch[v][i]) v = nxt[v];
                nxt[ch[u][i]] = ch[v][i];
            }
        }
    }
}

void calc(int id) {
    int u = 1, len = strlen(s[id]);
    int k;
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'a';
        u = ch[u][c];
        k = u;
        while (k > 1) {
            if (idx[k]) cnt[k]++;
            // int nk = nxt[nxt[k]];
            k = nxt[k];
            // if (nk > 1) nxt[k] = nk;
        }
    }
}

int dfs(int u) {
    if (u > 1 && idx[nxt[u]] == 0) return dfs(nxt[u]);
    if (idx[nxt[u]] > 0) return nxt[u];
    if (u == 1) return u;
    return 0;
}

void uni() {
    for (int i = 2; i <= tot; i++) {
        int fa = dfs(i);
        if (fa > 1) nxt[i] = fa;
    }
}

int get_ans(int id) {
    int u = 1, len = strlen(s[id]);
    int ans = 0;
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'a';
        u = ch[u][c];
        ans = cnt[u];
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i]);
        build_trie(i);
    }
    bfs();
    // 路径压缩，nxt[u]指向上一个最近的前缀匹配单词的节点，这样省去了中间无意义的nxt[u]操作
    uni();
    // for (int i = 2; i <= tot; i++) printf("%d %d\n", i, nxt[i]);
    for (int i = 1; i <= n; i++) {
        calc(i);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", get_ans(i));
    }

    return 0;
}
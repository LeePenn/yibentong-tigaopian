#include <bits/stdc++.h>
using namespace std;

const int N = 13, L = 55, Z = 26;
int ch[N * L][Z], tot = 1;
int b[N * L];
int n;
string s[N];
int que[N * L], q1, q2, nxt[N * L];
bool v[N * L][1 << N];
pair<pair<int, int>, int> pre[N * L][1 << N];

void build_trie(int id) {
    int u = 1, len = s[id].length();
    for (int i = 0; i < len; i++) {
        int c = s[id][i] - 'A';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    b[u] |= 1 << (id - 1);
}

void bfs() {
    for (int i = 0; i < Z; i++) ch[0][i] = 1;
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

int merge_sta(int u, int sta) {
    for (int i = u; i; i = nxt[i]) {
        sta |= b[i];
    }
    return sta;
}

void print_ans(int u, int sta) {
    if (u == 1 && sta == 0) return;
    
    print_ans(pre[u][sta].first.first, pre[u][sta].first.second);
    printf("%c", pre[u][sta].second + 'A');
}

void bfs2() {
    queue<pair<int, int>> q;
    q.push(make_pair(1, 0));
    v[1][0] = true;
    while (!q.empty()) {
        int u = q.front().first, sta = q.front().second; q.pop();
        for (int i = 0; i < Z; i++) {
            int nn = ch[u][i];
            int nsta = merge_sta(nn, sta);
            if (!v[nn][nsta]) {
                q.push(make_pair(nn, nsta));
                v[nn][nsta] = true;
                pre[nn][nsta] = {{u, sta}, i};
                if (nsta == (1 << n) - 1) {
                    print_ans(nn, nsta);
                    printf("\n");
                    return;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        build_trie(i);
    }
    
    bfs();
    bfs2();
    return 0;
}
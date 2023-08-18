#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 10, M = 1e5 + 10;
int ele[255];
int ch[M * 100][4], tot = 1;
int n, m;
bool b[M * 100];
string s1, s2[M];
int que[M * 100], q1, q2, nxt[M * 100];

void init_ele() {
    ele['E'] = 0, ele['S'] = 1, ele['W'] = 2, ele['N'] = 3;
}

void insert_trie(int id) {
    int u = 1, len = s2[id].length();
    for (int i = 0; i < len; i++) {
        int c = ele[s2[id][i]];
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
}

void bfs() {
    for (int i = 0; i < 4; i++) {
        ch[0][i] = 1;
    }
    q1 = 1, q2 = 1, nxt[1] = 0;
    que[1] = 1;
    while (q1 <= q2) {
        int u = que[q1++];
        for (int i = 0; i < 4; i++) {
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

void add_tag() {
    int u = 1, k;
    for (int i = 0; i < n; i++) {
        int c = ele[s1[i]];
        u = ch[u][c];
        k = u;
        while (k > 1 && !b[k]) {
            b[k] = true, k = nxt[k];
        }
    }
}

void find(int id) {
    int u = 1, len = s2[id].length();
    int ans = 0;
    for (int i = 0; i < len; i++) {
        int c = ele[s2[id][i]];
        u = ch[u][c];
        if (b[u]) ans++;
    }   
    printf("%d\n", ans);
}

int main() {
    cin >> n >> m;
    cin >> s1;
    init_ele();
    for (int i = 1; i <= m; i++) {
        cin >> s2[i];
        insert_trie(i);
    }
    bfs();
    // 打上主串匹配路径上的标记
    add_tag();
    for (int i = 1; i <= m; i++) {
        // 因为字典树是由s2建立的，所以走的一定是一条完整的当时建树的路径，而因为刚刚这条路径打过了标记
        // （标记一定连续，以为前缀=后缀），所以统计计数
        find(i);
    }
    
    
    return 0;
}                           
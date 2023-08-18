#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n;
int ch[N][26], tot = 1;
int b[N];
char s[N];
string s1[N];
int que[N], q1, q2, nxt[N];
int p_ptr[N], t_ptr[N], m_ptr[N];

void build_trie(int id) {
    int u = 1, len = s1[id].length();
    for (int i = 0; i < len; i++) {
        int c = s1[id][i] - 'a';
        if (!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    b[u] = len;
}

void bfs() {
    for (int i = 0; i < 26; i++) ch[0][i] = 1;
    nxt[1] = 0, que[1] = 1, q1 = 1, q2 = 1;
    while (q1 <= q2) {
        int u = que[q1++];
        for (int i = 0; i < 26; i++) {
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

void init_ptr() {
    int len = strlen(s + 1);
    for (int i = 1; i <= len + 1; i++) p_ptr[i] = i - 1;
    for (int i = 0; i <= len; i++) t_ptr[i] = i + 1;
}

void work() {
    int u = 1, len = strlen(s + 1), i = 1;
    while (i <= len) {
        int c = s[i] - 'a';
        u = ch[u][c];
        if (b[u]) {
            // printf("found %d %d\n", b[u], i);
            int last = i;
            for (int j = 0; j < b[u]; j++) {
                i = p_ptr[i];
            }
            // printf("last = %d, i = %d", last, i);
            t_ptr[i] = t_ptr[last];
            p_ptr[t_ptr[last]] = i;
            if (i == 0) {
                i = t_ptr[i];
                u = 1;
            } else {
                u = m_ptr[i];
                i = t_ptr[i];
            }
        } else {
            m_ptr[i] = u;
            i = t_ptr[i];
        }
    }
}

void print_ans() {
    int i = t_ptr[0], len = strlen(s + 1);
    while (i <= len) {
        printf("%c", s[i]);
        i = t_ptr[i];
    }
    printf("\n");
}

int main() {
    scanf("%s", s + 1);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        cin >> s1[i];
        build_trie(i);
    }
    bfs();
    init_ptr();
    work();
    print_ans();

    return 0;
}
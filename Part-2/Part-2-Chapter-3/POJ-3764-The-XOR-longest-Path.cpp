#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, Z = 32, B = 2;
int ch[N * Z][B], n_cnt = 1;

int n, u, v, w;

int hd[N], nx[N], to[N], cost[N], e_cnt = 0;

void build_edge(int a, int b, int c) {
    nx[++e_cnt] = hd[a];
    to[e_cnt] = b;
    cost[e_cnt] = c;
    hd[a] = e_cnt;
}

int nums[N];

void dfs(int r, int val) {
    if (hd[r] == 0) {
        nums[r] = val;
        return;
    }   
    for (int i = hd[r]; i; i = nx[i]) {
        int n_r = to[i];
        dfs(n_r, val ^ cost[i]);
    }
    nums[r] = val;
}

int ans = 0;

void calc() {
    for (int i = 1; i <= n; i++) {
        int r = 1;
        int maxx = 0;
        for (int j = 30; j >= 0; j--) {
            int c = (nums[i] >> j) & 1, cc = c ^ 1;
            if (ch[r][cc]) {
                maxx |= (1 << j);
                r = ch[r][cc];
            } else r = ch[r][c];
        }
        
        ans = max(maxx, ans);
    }

}

void build_trie() {
    for (int i = 1; i <= n; i++) {
        int r = 1;
        int cur = nums[i];
        for (int j = 30; j >= 0; j--) {
            int c = (cur >> j) & 1;
            if (!ch[r][c]) ch[r][c] = ++n_cnt;
            r = ch[r][c];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &u, &v, &w);
        build_edge(u, v, w);
    }
    dfs(1, 0);
    build_trie();
    calc();
    printf("%d\n", ans);
    
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
const int L = 32;
const int Z = 2;
int ch[N * L][Z], tot;
int a[N], n, ans;

void calc() {
    for (int i = 1; i <= n; i++) {
        int r = 0;
        int num = 0;
        for (int j = 30; j >= 0; j--) {
            int c = (a[i] >> j) & 1, cc = c ^ 1;
            if (ch[r][cc]) {
                r = ch[r][cc];
                num |= (1 << j);
            } else if (ch[r][c]) {
                r = ch[r][c];
            }
        }
        ans = max(ans, num);
    }
}

void build() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        int r = 0;
        for (int j = 30; j >= 0; j--) {
            int c = (a[i] >> j) & 1;
            if (!ch[r][c]) ch[r][c] = ++tot;
            r = ch[r][c];
        }
    }
}

int main() {
    scanf("%d", &n);
    tot = 0;
    build();
    ans = 0;
    calc();
    printf("%d\n", ans);

    return 0;
}
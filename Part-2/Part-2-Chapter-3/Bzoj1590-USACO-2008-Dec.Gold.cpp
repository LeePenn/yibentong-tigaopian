#include <bits/stdc++.h>

using namespace std;

const int N = 500005;
const int M = 100005;
const int Z = 2;
int ch[N][Z], tot = 0;
int n, m, l;
char temp[1];
char s[M];
int cnt[N], ed[N];

void insert() {
    int r = 0;
    for (int i = 1; i <= l; i++) {
        int c = s[i] - '0' + 1;
        if (!ch[r][c]) ch[r][c] = ++tot;
        r = ch[r][c];
        cnt[r]++;
    }
    ed[r]++;
    cnt[r]--;
}

void work() {
    int r = 0;
    int ans = 0, edCnt = 0;
    for (int i = 1; i <= l; i++) {
        int c = s[i] - '0' + 1;
        if (!ch[r][c]) {
            ans = 0;
            break;
        }
        r = ch[r][c];
        ans = cnt[r];
        edCnt += ed[r];
    }
    // printf("ans = %d, edCnt = %d\n", ans, edCnt);
    printf("%d\n", ans + edCnt);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &l);
        for (int j = 1; j <= l; j++) {
            scanf("%s", temp);
            s[j] = temp[0];
        }
        s[l + 1] = '\0';
        insert();
    }
    
    for (int i = 1; i <= m; i++) {
        scanf("%d", &l);
        for (int j = 1; j <= l; j++) {
            scanf("%s", temp);
            s[j] = temp[0];
        }
        s[l + 1] = '\0';
        // printf("%s\n", s + 1);
        work();
    }
    
    // printf("%d\n", tot);
    // for (int i = 1; i <= tot; i++) printf("%d ", cnt[i]);
    // printf("\n");

    return 0;
}
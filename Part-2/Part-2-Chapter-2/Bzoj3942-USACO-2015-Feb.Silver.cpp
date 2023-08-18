#include <bits/stdc++.h>

using namespace std;

const int N = 1000005;
char s[N], t[N];
int n, m, p[N];
int nx[N], pre[N], ptr[N];

void init() {
    p[1] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j && t[i + 1] != t[j + 1]) j = p[j];
        if (t[i + 1] == t[j + 1]) j++;
        p[i + 1] = j;
    }
    // for (int i = 1; i <= m; i++) printf("%d ", p[i]);
    // exit(0);
    
    for (int i = 0; i <= n; i++) nx[i] = i + 1;
    for (int i = n + 1; i >= 1; i--) pre[i] = i - 1;
}

void work() {
    int i = 0, j = 0;
    while (i <= n && nx[i] <= n + 1) {
        // printf("%d %d \n", i, nx[i]);
        while (j && s[nx[i]] != t[j + 1]) j = p[j];
        if (s[nx[i]] == t[j + 1]) {
            j++;
            ptr[nx[i]] = j;
            // printf("%d %d\n", nx[i], j);
            // exit(0);
        }
        if (j == m) {
            // printf("%d %d\n", nx[i], j);
            // exit(0);
            int nxx = nx[nx[i]];
            i = nx[i];
            for (int k = 1; k <= m; k++) i = pre[i];
            nx[i] = nxx;
            pre[nxx] = i;
            j = ptr[i];
            // printf("%d %d %d %d %d\n", i, nx[i], nxx, pre[nxx], j);
            // for (int k = 0; k < n; k = nx[k]) printf("%c", s[nx[k]]);
            // printf("\n");
            
        } else {
            i = nx[i];
        }
    }
    for (int i = 0; i <= n && nx[i] <= n; i = nx[i]) printf("%c", s[nx[i]]);
    printf("\n");

}

int main() {    
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    init();
    work();

    return 0;
}
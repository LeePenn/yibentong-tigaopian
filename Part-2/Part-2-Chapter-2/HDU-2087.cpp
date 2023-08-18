#include <bits/stdc++.h>

using namespace std;

const int N = 1004;
int n, m;
int p[N];
char s1[N], s2[N];
int ans;

void init() {
    p[1] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && s2[i + 1] != s2[j + 1]) j = p[j];
        if (s2[i + 1] == s2[j + 1]) j++;
        p[i + 1] = j;
    }
    
}

void work() {
    int last = -1;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s1[i + 1] != s2[j + 1]) j = p[j];
        if (s1[i + 1] == s2[j + 1]) j++;
        if (j == m) {
            if (i + 1 - m + 1 <= last) j = p[j];
            else {
                ans++;
                last = i + 1;
                j = p[j];
            }
        }
    }


}

int main() {
    while (scanf("%s", s1 + 1) == 1 && strcmp(s1 + 1, "#") != 0) {
        scanf("%s", s2 + 1);
        n = strlen(s1 + 1), m = strlen(s2 + 1);
        init();
        ans = 0;
        work();
        printf("%d\n", ans);
    }
    return 0;
}
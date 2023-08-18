#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 20000;
int k, p[N], n, fa[N];
char s[N];
LL ans;

void work(char s1[]) {
    int len = strlen(s1 + 1);
    p[1] = 0;
    memset(fa, 0, sizeof(fa));
    for (int i = 1, j = 0; i < len; i++) {
        while (j && s1[i + 1] != s1[j + 1]) j = p[j];
        if (s1[i + 1] == s1[j + 1]) j++;
        p[i + 1] = j; fa[i + 1] = j;
        if (fa[j]) {
            fa[i + 1] = fa[j];
        } else {
            // 只压缩需要压缩的路径, 之前的可以, 那么这个也可以
            if (j >= k) fa[i + 1] = j;
            // 小于k的都排除
            else fa[i + 1] = 0;
        }
        if (fa[i + 1] >= k && 2 * fa[i + 1] + 1 <= i + 1) {
            ans++;
        } 
    }
}

int main() {
    scanf("%s", s + 1);
    scanf("%d", &k);
    n = strlen(s + 1);
    ans = 0;
    for (int i = 0; i <= n; i++) {
        work(s + i);
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 1000005;
int n, p[N];
char s[N];

void work() {
    p[1] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && s[i + 1] != s[j + 1]) j = p[j];
        if (s[i + 1] == s[j + 1]) j++;
        p[i + 1] = j;
    }
    
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        int j = i;
        while (j && p[j]) j = p[j];
        if (p[i]) p[i] = j;
        ans += i - j;
    } 
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    work();

    return 0;
}
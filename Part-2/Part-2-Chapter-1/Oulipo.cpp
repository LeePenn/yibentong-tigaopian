#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1000006;
LL sum[N], p[N];
LL s, b;
char s1[N], s2[N];

void init() {
    p[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * b;
    }
}

int main() {
    b = 31;
    init();
    
    scanf("%s%s", s1 + 1, s2 + 1);
    int l1 = strlen(s1 + 1), l2 = strlen(s2 + 1);
    s = 0;
    for (int i = 1; i <= l2; i++) {
        s = s * b + (LL)(s2[i] - 'A' + 1);
    }
    
    sum[0] = 0;
    for (int i = 1; i <= l1; i++) {
        sum[i] = sum[i - 1] * b + (LL)(s1[i] - 'A' + 1);
    }
    
    int ans = 0;
    for (int i = l2; i <= l1; i++) {
        if (s == sum[i] - sum[i - l2] * p[l2]) ans++;
    }
    printf("%d\n", ans);

    return 0;
}
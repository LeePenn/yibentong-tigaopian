#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 400004;
LL sum[N], p[N], b = 31;
char s[N];

void init() {
    p[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * b;
    }
}

int main() {
    init();
    while (scanf("%s", s + 1) == 1) {
        int l = strlen(s + 1);
        sum[0] = 0;
        for (int i = 1; i <= l; i++) {
            sum[i] = sum[i - 1] * b + (LL)(s[i] - 'a' + 1);
        }
        for (int i = 1; i < l; i++) {
            
            if (sum[i] == sum[l] - sum[l - i] * p[i]) {
                printf("%d ", i);
            }
        }
        printf("%d\n", l);
    }

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 1000005;
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
    while (scanf("%s", s + 1) == 1 && s[1] != '.') {
        int l = strlen(s + 1);
        sum[0] = 0;
        for (int i = 1; i <= l; i++) {
            sum[i] = sum[i - 1] * b + (LL)(s[i] - 'a' + 1);
        }
        
        bool found = false;
        int i;
        for (i = 1; i <= l / 2; i++) {
            if (l % i != 0) continue;
            bool ok = true;
            for (int j = i; j <= l; j += i) {
                if (sum[j] - sum[j - i] * p[i] != sum[i]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                found = true;
                break;
            }
        }
        if (found) {
            printf("%d\n", l / i);
        } else {
            printf("1\n");
        }
    }
    
    return 0;
}
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 500004;
char s[N];
int n, q;
LL p[N], sum[N], b = 31;
bool is_prime[N];
int prime[N], tot;
int l, r;
int a[N];

void init1() {
    p[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * b;
    }
}

void init2() {
    // 41538
    is_prime[1] = false;
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            prime[++tot] = i;
            for (int j = 2; j * i < N; j++) {
                is_prime[j * i] = false;
            }
        }
    }
}

void init3() {
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] * b + (s[i] - 'a' + 1);
    }
}

int get_hash(int l, int r) {
    return sum[r] - sum[l - 1] * p[r - l + 1];
}

// key idea => check long part
int check(int l, int r, int i) {
    return get_hash(l + i, r) == get_hash(l, r - i);
}

int main() {
    memset(is_prime, 1, sizeof(is_prime));
    init1();
    init2();
    scanf("%d", &n);
    scanf("%s", s + 1);
    init3();
    
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &l, &r);
        int len = r - l + 1;
        int cnt = 0;
        int x = len;
        for (int i = 1; i <= tot && prime[i] * prime[i] <= x; i++) {
            if (x % prime[i] == 0) {
                a[++cnt] = prime[i];
                while (x % prime[i] == 0) {
                    x /= prime[i];
                }
            }
        }
        if (x > 1) a[++cnt] = x;
        
        x = len;
        for (int i = 1; i <= cnt; i++) {
            while (x % a[i] == 0 && check(l, r, x / a[i])) x /= a[i];
        }
        
        printf("%d\n", x);
    }
    
    return 0;
}
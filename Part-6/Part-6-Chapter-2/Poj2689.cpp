#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
LL L, R;
LL v[N], prime[N], tot, b[N];
bool vis[N];

int ReadInt() {
    int r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

LL ReadLL() {
    LL r = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        r = (r << 1) + (r << 3) + ch - 48;
        ch = getchar();
    }

    return r * f;
}

void Init() {
    for (int i = 2; i < 46340; ++i) {
        if (!v[i]) {
            v[i] = i;
            prime[++tot] = i;
        }
        
        for (int j = 1; j <= tot; ++j) {
            if (prime[j] > v[i] || prime[j] * i > 46340) break;
            
            v[prime[j] * i] = prime[j];
        }
    }
}

void Work() {
    while (scanf("%lld%lld", &L, &R) == 2) {
        memset(vis, 1, sizeof(vis));
        if (L == 1) vis[0] = 0;
        
        for (int i = 1; i <= tot; ++i) {
            for (LL j = L / prime[i]; prime[i] * j <= R; ++j) {
                if (j > 1) {
                    // 标记合数
                    vis[prime[i] * j - L] = 0;
                }
            }
        }
        
        int cnt = 0;
        for (LL i = L; i <= R; ++i) {
            if (vis[i - L]) b[++cnt] = i;
            if (i == R) break;
        }
        
        LL minn = 2147483647, maxx = 0;
        LL minnX, minnY, maxxX, maxxY;
        for (int i = 1; i < cnt; ++i) {
            LL j = b[i + 1] - b[i];
            if (j > maxx) {
                maxx = j; 
                maxxX = b[i];
                maxxY = b[i + 1];
            }
            if (j < minn) {
                minn = j;
                minnX = b[i];
                minnY = b[i + 1];
            }
        }
        
        if (!maxx) {
            printf("There are no adjacent primes.\n");
        } else {
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", minnX, minnY, maxxX, maxxY); 
        }
    }   
}

int main() {
    Init();
    
    Work();


    return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int N = 400009;
const int L = 32;
const int Z = 2;
int n, a[N];
int ch[N * L][Z], tot;
int suml[N], sumr[N], maxl[N], maxr[N];

void insert(int t) {
    int r = 0;
    for (int i = 30; i >= 0; i--) {
        int c = (t >> i) & 1;
        if (!ch[r][c]) {
            ch[r][c] = ++tot;
        }
        r = ch[r][c];
    }
}

int main() {
    scanf("%d", &n);
    tot = 0;
    // left
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        suml[i] = a[i] ^ suml[i - 1];
        insert(suml[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        int r = 0;
        int num = 0;
        for (int j = 30; j >= 0; j--) {
            int c = (suml[i] >> j) & 1, cc = c ^ 1;
            if (ch[r][cc]) {
                r = ch[r][cc];
                num |= (1 << j);
            } else if (ch[r][c]) {
                r = ch[r][c];
            }
        }
        maxl[i] = num;
    }
    
    // right
    memset(ch, 0, sizeof(ch));
    for (int i = n; i >= 1; i--) {
        sumr[i] = a[i] ^ sumr[i + 1];
        insert(sumr[i]);
    }
    
    for (int i = n; i >= 1; i--) {
        int r = 0;
        int num = 0;
        for (int j = 30; j >= 0; j--) {
            int c = (sumr[i] >> j) & 1, cc = c ^ 1;
            if (ch[r][cc]) {
                r = ch[r][cc];
                num |= (1 << j);
            } else if (ch[r][c]) {
                r = ch[r][c];
            }
        }
        maxr[i] = num;
    }
    
    // calc
    int curmaxl = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        curmaxl = max(curmaxl, maxl[i]);
        ans = max(ans, curmaxl + maxr[i + 1]);
    }
    
    printf("%d\n", ans);
    
    

    return 0;
}
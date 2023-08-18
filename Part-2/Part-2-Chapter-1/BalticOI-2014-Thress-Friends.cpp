#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 20000005;
LL p[N], sum[N], b = 13331;
int n;
char s[N];
char ans[N];

void init() {
    p[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * b;
    }
}

bool check(int k) {
    int half1 = n >> 1, half2 = (n + 1) >> 1;
    if (k < half2) {
        int l1 = k - 1, l2 = half2 - k;
        LL hash11 = sum[l1];
        LL hash21 = sum[half2] - sum[k] * p[l2];
        
        LL hash12 = sum[half2 + k - 1] - sum[half2] * p[k - 1];
        LL hash22 = sum[n] - sum[n - l2] * p[l2];
        
        if (hash11 != hash12) return false;
        if (hash21 != hash22) return false;
    } else if (k == half2) {
        if (sum[n] - sum[k] * p[n / 2] != sum[n / 2]) return false;
    } else if (k > half2) {
        int l1 = k - half1 - 1, l2 = n - k;
        LL hash11 = sum[l1];
        LL hash12 = sum[k - 1] - sum[half1] * p[l1];
        
        LL hash21 = sum[half1] - sum[l1] * p[l2];
        LL hash22 = sum[n] - sum[k] * p[l2];
        
        if (hash11 != hash12) return false;
        if (hash21 != hash22) return false;
    }
    
    return true;
}

bool check_same(int i1, int i2) {
    return s[i1] == s[i1 + 1] && s[i2] == s[i2 - 1];
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    init();
    
    if (n % 2 == 0) {
        printf("NOT POSSIBLE\n");
        return 0;
    }
    
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] * b + (LL)(s[i] - 'A' + 1);
    }
    
    int insertIdx = -1;
    for (int i = 1; i <= n; i++) {
        if (check(i)) {
            if (insertIdx == -1) {
                int t = 0;
                for (int j = 1; j <= n; j++) {
                    if (j == i) continue;
                    ans[++t] = s[j];
                }
                insertIdx = i;
            } else {
                if (!check_same(insertIdx, i)) {
                    printf("NOT UNIQUE\n");
                    return 0;
                }
            }
        }
    }
    
    if (insertIdx == -1) {
        printf("NOT POSSIBLE\n");
        return 0;
    }
    // printf("%d\n", insertIdx);
    for (int i = 1; i <= (n >> 1); i++) {
        printf("%c", ans[i]);
    }
    printf("\n");
    

    return 0;
}
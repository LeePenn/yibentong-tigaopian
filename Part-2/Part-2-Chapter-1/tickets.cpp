#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 2000005;
const int P = 1333331;

int A, B, C;
LL hd[N], ne[N], num[N], tot;

LL calc(LL a) {
    return (A * a + a % B) % C;
}

LL get_hash(LL a) {
   return (calc(a)) % P;
}

void Add(LL a) {
    LL h = get_hash(a);
    ne[++tot] = hd[h];
    hd[h] = tot;
    num[tot] = a;
}

bool Find(LL a) {
    int h = get_hash(a);
    for (LL i = hd[h]; i; i = ne[i]) {
        if (num[i] == a) return true;
    }
    return false;
}

int main() {
    scanf("%d%d%d", &A, &B, &C);
    
    LL a = 1;
    Add(a);
    bool found = false;
    for (int i = 1; i <= 2000000; i++) {
        a = calc(a);
        if (Find(a)) {
            printf("%d\n", i);
            found = true;
            break;
        } 
        Add(a);
    }
    if (!found) printf("-1\n");
    return 0;
}
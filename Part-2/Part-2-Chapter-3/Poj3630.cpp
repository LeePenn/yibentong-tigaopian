#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
const int B = 10;
int t[N][B], tot;
char a[20];
bool b[N];
int T, n;

bool insert() {
    int l = strlen(a + 1);
    bool flag = false;
    int r = 1;
    for (int i = 1; i <= l; i++) {
        int c = a[i] - '0';
        if (!t[r][c]) t[r][c] = ++tot;
        else if (i == l) flag = true;
        r = t[r][c];
        if (b[r]) flag = true;
    }
    b[r] = true;
    return flag;
    
}

void work() {
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        scanf("%s", a + 1);
        if (insert()) flag = true;
    }
    if (flag) printf("NO");
    else printf("YES");
    printf("\n");
    

}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        tot = 1;
        memset(t, 0, sizeof(t));
        memset(b, 0, sizeof(b));
        work();
    }

    return 0;
}

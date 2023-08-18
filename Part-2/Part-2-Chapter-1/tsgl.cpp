#include <bits/stdc++.h>

using namespace std;

const int N = 30011;
int n, h = N, b = 31;
string books[N];
char op[10];
int hd[N], nx[N];
string t;
int tot;

int calc_hash(const string &s) {
    int l = s.length();
    int ret = 0;
    for (int i = 0; i < l; i++) {
        ret = ret * b + (s[i] - '\0' + 1);
        ret %= N;
    }
    return ret;
}

void Add() {
    getchar();
    getline(cin, t);
    
    // printf("%s\n", t.c_str());
    int h = calc_hash(t);
    for (int i = hd[h]; i > 0; i = nx[i]) {
        if (books[i] == t) return;
    }
    
    nx[++tot] = hd[h]; hd[h] = tot;
    books[tot] = t;
}

bool Find() {
    getchar();
    getline(cin, t);
    int h = calc_hash(t);
    // printf("%s\n", t.c_str());
    for (int i = hd[h]; i > 0; i= nx[i]) {
        if (books[i] == t) return true;
    }
    return false;
}

void work() {
    cin >> op;
    if (strcmp(op, "add") == 0) {
        Add();
    } else if (strcmp(op, "find") == 0) {
        if (Find()) printf("yes");
        else printf("no");
        printf("\n");
    }
    
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        work();
    }
    


    return 0;
}
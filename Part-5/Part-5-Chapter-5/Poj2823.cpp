#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, k;
int a[N], Fmax[N], Fmin[N];
int q[N], num[N] = {0}, head, tail;

void Read() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}

void DPMin() {
    head = 1, tail = 0;
    for (int i = 1; i <= n; ++i) {
        while (num[head] < i - k + 1 && head <= tail) head++;
        while (a[i] <= q[tail] && head <= tail) tail--;
        num[++tail] = i;
        q[tail] = a[i];
        Fmin[i] = q[head];
    }
}

void DPMax() {
    head = 1, tail = 0;
    for (int i = 1; i <= n; ++i) {
        while (num[head] < i - k + 1 && head <= tail) head++;
        while (a[i] >= q[tail] && head <= tail) tail--;
        num[++tail] = i;
        q[tail] = a[i];
        Fmax[i] = q[head];
    }
}

void Print() {
    for (int i = k; i <= n; ++i) cout << Fmin[i] << ' ';
    cout << endl;
    for (int i = k; i <= n; ++i) cout << Fmax[i] << ' ';
    cout << endl;
}

int main() {
    Read();
    
    DPMin();
    DPMax();
    Print();

    return 0;
}
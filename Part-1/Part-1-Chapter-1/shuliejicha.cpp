#include <bits/stdc++.h>

using namespace std;

int n, a[50005], mod;
priority_queue<int, vector<int>> q1;
priority_queue<int, vector<int>, greater<int>> q2;


int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        q1.push(a[i]);
        q2.push(a[i]);
    }

    while (q1.size() > 1) {
        int a1 = q1.top();
        q1.pop();
        int a2 = q1.top();
        q1.pop();
        int maxx = a1 * a2 + 1;
        q1.push(maxx);

        int b1 = q2.top();
        q2.pop();
        int b2 = q2.top();
        q2.pop();
        int minn = b1 * b2 + 1;
        q2.push(minn);
    }

    int maxx = q1.top();
    int minn = q2.top();
    cout << abs(maxx - minn) << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 99;
int n, p[N];
char a[N];
void pre() {
    int j = 0;
    p[1] = 0;

    for (int i = 1; i < n; i++) {
        while (j > 0 && a[i + 1] != a[j + 1])
            j = p[j];

        if (a[i + 1] == a[j + 1])
            j++;

        p[i + 1] = j;
    }
}
int main() {
    cin >> n;
    scanf("%s", a + 1);
    pre();
    //  for(int i=1;i<=n;i++){
    //      cout<<p[i]<<" ";
    //  }cout<<endl;
    cout << n - p[n] << endl;
    return 0;
}
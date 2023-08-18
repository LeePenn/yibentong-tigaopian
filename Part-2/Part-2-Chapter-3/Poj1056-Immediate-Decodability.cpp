#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int L = 12;
const int Z = 2;
int ch[N * L][Z], tot = 0;
bool b[N * L];
char s[20];
bool found = false;
int T = 1;

void insert() {
    int l = strlen(s + 1);
    int r = 0;
    for (int i = 1; i <= l; i++) {
        int c = s[i] - '0';
        if (!ch[r][c]) ch[r][c] = ++tot;
        else if (i == l) {
            found = true;
        }
        r = ch[r][c];
        if (b[r]) found = true;
    }
    b[r] = true;


}

int main() {
    while (scanf("%s", s + 1) == 1) {
        if (strcmp(s + 1, "9") == 0) {
            if (found) printf("Set %d is not immediately decodable\n", T);
            else printf("Set %d is immediately decodable\n", T);
            T++;
            memset(b, 0, sizeof(b));
            memset(ch, 0, sizeof(ch));
            tot = 0;
            found = false;
        } else {
            insert();
        }
    } 

    return 0;
}
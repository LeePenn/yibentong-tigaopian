#include <cstdio>
#include <cstring>

const int MAXN = 10000010;
const int MAXM = 1000010;
const int MAXL = 105;

int n, m, l;
char dir[128];
char a[MAXN];
char b[MAXM][MAXL];
int next[MAXN], q[MAXN];
int path[MAXN][4];
bool check[MAXN];

void init()
{
   int i, cur;
   char *c;
   dir['W'] = 0;
   dir['N'] = 1;
   dir['E'] = 2;
   dir['S'] = 3;
   scanf("%d %d\n", &n, &m);
   gets(a);
   l = 1;
   memset(path, 0, sizeof(path));
   i = m;
   while (i--)
   {
      gets(b[i]);
      cur = 1;
      for (c=b[i]; (*c)!='\0'; ++c)
      {
         if (path[cur][dir[*c]] == 0)
            path[cur][dir[*c]] = ++l;
         cur = path[cur][dir[*c]];
      }
   }
}

void build_dfa()
{
   int i, j;
   int *st, *ed;
   st = ed = q;
   next[1] = 1;
   for (j=0; j<4; ++j)
   if (path[1][j] == 0)
      path[1][j] = 1;
   else
   {
      next[path[1][j]] = 1;
      *(ed++) = path[1][j];
   }
   while (st != ed)
   {
      i = *(st++);
      for (j=0; j<4; ++j)
      if (path[i][j] == 0)
         path[i][j] = path[next[i]][j];
      else
      {
         next[path[i][j]] = path[next[i]][j];
         *(ed++) = path[i][j];
      }
   }
}

void solve()
{
   int i, ans, cur = 1;
   char *c;  
   build_dfa();
   memset(check, 0, sizeof(check));
   for (c=a; (*c)!='\0'; ++c)
      check[cur = path[cur][dir[*c]]] = true;
   int *st, *ed;
   for (ed=q+l,st=q; ed!=st; --ed)
      check[next[*ed]] |= check[*ed];
   i = m;
   while (i--)
   {
      cur = 1;
      ans = 0;
      for (c=b[i]; (*c)!='\0'; ++c)
      if (check[cur = path[cur][dir[*c]]]) 
         ++ans;
      else break;
      printf("%d\n", ans);
   }
}

int main()
{
   freopen("symbol.in", "r", stdin);
   freopen("symbol.out", "w", stdout);
   init();
   solve();
   return 0;
}

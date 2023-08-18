#include<cstdio>
#include<cstring>
using namespace std;
int a[105],bo[105],ans[105];
int n,m;
bool check(int v,int x)
{
	for (int i=0; i<=x; ++i)
	if (v-a[i]>=0 && bo[v-a[i]]) return 1;
	return 0;
}
void dfs(int x)
{
	if (x>=m) return;
	if (a[x]==n) {
		if (x<m) m=x,memcpy(ans,a,sizeof(ans)); 		
		return;
	}
	for (int j=n; j>a[x]; --j)
	if (check(j,x)){
		a[x+1]=j;
		bo[j]=1;
		dfs(x+1);
		bo[j]=0;
	}
	return;
}
int main()
{
	bo[1]=1;
	a[0]=1;
	while (scanf("%d",&n),n){
		for (int i=2; i<=n; ++i) bo[i]=0;
		m=1e5;
		dfs(0);
		for (int i=0; i<=m; ++i) printf("%d ",ans[i]);
		printf("\n");
	}
}

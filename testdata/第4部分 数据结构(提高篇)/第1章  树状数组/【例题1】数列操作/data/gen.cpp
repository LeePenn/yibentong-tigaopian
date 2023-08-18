#include <cstdio>  
#include <algorithm> 
#include <vector>  
#include <ctime>  
#include <cstdlib>  
using namespace std;
int n=1e5,m=1e5;
int Rand()
{
	int x=rand();
	return x*rand()+rand();
}
int main()
{
	freopen("test10.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	for (int i=1; i<=n; ++i) printf("%d ",rand()%1000);
	printf("\n");
	for (int i=1; i<=m; ++i) {
		int t=rand()%2,l=Rand()%n+1,r=Rand()%n+1;
		if (t==0) {
			if (l>r) swap(l,r);
		}		
		else r%=1000;
		printf("%d %d %d\n",t,l,r);
	}
}

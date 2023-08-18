#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <math.h>

#define inf (2147483647)
#define sqr(a) (a*a)
#define Fv(i,v) for (int i=0;i<v;i++)
#define Mkp(p,q) make_pair(p,q)

#define LL long long

using namespace std;

LL A, B, C;
int D;

int check(int m) {
	LL prev=1, now;
	for(int i=1;i<=m;++i) {
		now = ( A*prev + prev % B) % C;
		prev=now;
	}
	LL tar = prev;
	for(int j=1;j<=D;++j) {
		now = ( A*prev + prev % B) % C;
		prev=now;
	}
	return prev == tar;
}

int main() {
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	cin>>A>>B>>C;
	int i = 1, j;
	
	LL prev=1, now;
	for(i=1;i<=2*1000000;++i) {
		now = ( A*prev + prev % B) % C;
		if(now==1) {
			cout<<i<<endl; 
			scanf("%*s");
			exit(0);
		}
		prev=now;
	}
	
	D = -1;
	
	LL tar = prev;
	for(j=1;j<=2*1000000;++j) {
		now = ( A*prev + prev % B) % C;
		if(now==tar) {
			D = j; break;
		}
		prev=now;
	}
	
	if(D<0) {
		cout<<-1<<endl; exit(0);
	}
	
	prev = 1;
	for(j=1;j<=D;++j) {
		now = ( A*prev + prev % B) % C;
		prev=now;
	}
	
	LL p1 = prev, n1;
	prev = 1;
	
	for(i=1;1;++i) {
		now = ( A*prev + prev % B) % C;
		n1 = (A*p1+p1%B)%C;
		if(now==n1) break;
		prev=now; p1=n1;
	}
	if (i+D>2000000&&i<2000000) {cout << "!!!" <<endl;return 0;}
	//cout <<"__"<< D <<endl;
	if(i+D > 2000000) cout<<-1<<endl;
	else 
	cout<<i+D<<endl;
	
	scanf("%*s");
}

// 2305843009213693951 1 9223372036854775807

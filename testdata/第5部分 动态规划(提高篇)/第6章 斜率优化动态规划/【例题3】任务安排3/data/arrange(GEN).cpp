#include<iostream>
#include<stdio.h>
#include<time.h>

using namespace std ;

int main() {
	srand(time(0)) ;
	freopen("arrange.in", "w", stdout) ;
	int N, S ;
	scanf("%d", &N) ;
	printf("%d %d\n", N, 
		rand() % 256) ;
	while (N--) 
		printf("%d %d\n",
			rand() % 512 - 256,
			rand() % 256) ;
	return 0 ;
}


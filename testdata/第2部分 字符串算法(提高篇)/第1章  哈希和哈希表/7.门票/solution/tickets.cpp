#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <iterator>
#include <bitset>
#include <sstream>
#include <cmath>
#include <cstring>

using namespace std;


int main(){
	//freopen("test.in","r",stdin);
	freopen("seq.in","w",stdout);
	srand(time(0)+rand());
	long long p=rand()%10000,q=rand()%10000,r=rand()%10000;
	p*=100000;q*=100000;r*=100000;
	p+=rand();q+=rand();r+=rand();
	cout << p << " " << q << " " << r <<endl;
	//system("pause");
	return 0;
}

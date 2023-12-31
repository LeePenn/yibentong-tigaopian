/*
  Play on Words
  CERC 1999, Tomas Brejcha
*/

#include <stdio.h>
#include <string.h>

#define EXISTS 1

int leters[500];
int s[500];
int flags[500];
char word[10000];

void go()
{
	int i, j, n, m1, p1, err, x;
	char c;
	for (i=0; i<130; i++) {leters[i] = flags[i] = 0; s[i] = i;}
	scanf("%i", &n);
	for (i=0; i<n; i++)
	{
		scanf("%s", word);
		leters[word[0]]++;
		leters[c = (strrchr(word, 0)[-1])]--;
		for (j=0; j<130; j++) if (s[j] == s[c]) s[j] = s[word[0]];
		flags[word[0]] |= EXISTS; flags[c] |= EXISTS;
	}

	m1 = p1 = err = 0; x = -1;
	for (i=0; i<130; i++) if (EXISTS & flags[i])
	{
		if (leters[i]==0) 
		{
			if (x != s[i]) if (x == -1) x = s[i];
							else err = 1;
		}
		else if (leters[i] == -1) if (m1) err = 1;
									else m1 = 1;
		else if (leters[i] == 1) if (p1) err = 1;
									else p1 = 1;
		else err=1;
	}
	if (err) printf("The door cannot be opened.\n");
	else printf("Ordering is possible.\n");
}

int main()
{
	int i,m;
	scanf("%i",&m);
	for (i=0; i<m; i++) go();
	return 0;
}


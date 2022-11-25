#include <bits/stdc++.h>
using namespace std;

char s1[1000010], s2[1000010];
int nxt[1000010];
int lena, lenb;

int main() {
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	lena = strlen(s1 + 1);
	lenb = strlen(s2 + 1);
	int j = 0;
	for (int i=2; i<=lenb; i++) {
		while(j && s2[i] != s2[j+1])
			j = nxt[j];
		if(s2[i] == s2[j+1]) j++;
		nxt[i] = j;
	}
	j = 0;
	for(int i=1; i<=lena; i++) {
		while(j && s1[i] != s2[j+1])
			j = nxt[j];
		if(s1[i] == s2[j+1]) j++;
		if(j == lenb) {
			printf("%d\n", i - lenb + 1);
			j = nxt[j];
		}
	}
	for(int i=1; i<=lenb; i++)
		printf("%d ", nxt[i]);
	return 0;
}

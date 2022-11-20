#include <bits/stdc++.h>
using namespace std;

int n, m;
int tr[5000000][30], tot;
int f[5000000], tag[5000000];
char str[5000000];

int getnum(char ch) {
	return ch - 'a';
}

void insert(char s[]) {
	int p = 0, len = strlen(s+1);
	for(int i=1; i<=len; i++) {
		int c = getnum(s[i]);
		if(!tr[p][c]) tr[p][c] = ++tot;
		p = tr[p][c];
		if(tag[p]) f[i] = 1;
	}
	tag[p] = 1;
}

void find(char s[], int st, int ed) {
	int p = 0, len = strlen(s+1);
	for(int i=st; i<=ed; i++) {
		int c = getnum(s[i]);
		if(!tr[p][c]) return;
		p = tr[p][c];
		if(tag[p]) f[i] = 1;
	}
	return;
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++) {
		scanf("%s", str+1);
		insert(str);
	}
	f[0] = 1;
	for(int i=1; i<=m; i++) {
		scanf("%s", str+1);
		int l = strlen(str+1);
		for(int j=1; j<=l; j++)
			f[j] = 0;
		for(int j=0; j<=l; j++)
			if(f[j]) find(str, j+1, l);
		for(int j=l; j>=0; j--) {
			if(f[j]) {
				printf("%d\n", j);
				break;
			}
		}
	}
	return 0;
}

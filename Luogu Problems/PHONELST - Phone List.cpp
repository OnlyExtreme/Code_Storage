#include <bits/stdc++.h>
using namespace std;

int trie[1000010][15], tot, cnt[1000010];
int t, n;
char s[100010][20];

int getnum(char ch) {
	return ch - '0';
}

void insert(char str[]) {
	int p = 0, len = strlen(str+1);
	for(int i=1; i<=len; i++) {
		int c = getnum(str[i]);
		if(!trie[p][c])
			trie[p][c] = ++tot;
		p = trie[p][c];
		cnt[p]++;
	}
}

int find(char str[]) {
	int p = 0, len = strlen(str+1);
	for(int i=1; i<=len; i++) {
		int c = getnum(str[i]);
		if(!trie[p][c])
			return 0;
		p = trie[p][c];
	}
	return cnt[p];
}

int main() {
	scanf("%d", &t);
	while(t--) {
		for(int i=0; i<=tot; i++)
			for(int j=0; j<=12; j++)
				trie[i][j] = 0;
		for(int i=0; i<=tot; i++)
			cnt[i] = 0;
		tot = 0;
		scanf("%d", &n);
		for(int i=1; i<=n; i++) {
			scanf("%s", s[i]+1);
			insert(s[i]);
		}
		bool flag = false;
		for(int i=1; i<=n; i++) {
			int x = find(s[i]);
			if(x > 1)
				flag = true;
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}

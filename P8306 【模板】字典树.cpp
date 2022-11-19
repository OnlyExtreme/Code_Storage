#include <bits/stdc++.h>
using namespace std;

int T;
int n, q;
int tr[3000005][70], idx, cnt[3000005];
char s[3000005];

// mapping: A~Z->1~26  a~z->27~52  0~9->53~62
int getnum(char ch) {
	if(isupper(ch))
		return int(ch - 'A');
	else if(islower(ch))
		return int(ch - 'a' + 26);
	else
		return int(ch - '0' + 52);
}

void insert(char str[]) {
	int p = 0, len = strlen(str+1);
	for(int i=1; i<=len; i++) {
		int c = getnum(str[i]);
		if(!tr[p][c])
			tr[p][c] = ++idx;
		p = tr[p][c];
		cnt[p]++;
	}
}

int find(char str[]) {
	int p = 0, len = strlen(str+1);
	for(int i=1; i<=len; i++) {
		int c = getnum(str[i]);
		if(!tr[p][c])
			return 0;
		p = tr[p][c];
	}
	return cnt[p];
}

int main() {
	scanf("%d", &T);
	while(T--) {
		for(int i=0; i<=idx; i++)
			for(int j=0; j<=69; j++)
				tr[i][j] = 0;
		for(int i=0; i<=idx; i++)
			cnt[i] = 0;
		idx = 0;
		scanf("%d %d", &n, &q);
		for(int i=1; i<=n; i++) {
			scanf("%s", s+1);
			insert(s);
		}
		for(int i=1; i<=q; i++) {
			scanf("%s", s+1);
			printf("%d\n", find(s));
		}
	}
	return 0;
}

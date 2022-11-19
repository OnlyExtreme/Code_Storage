#include <bits/stdc++.h>
using namespace std;

int m, n;
int a[50000], tot;
int trie[5000000][3], way[5000000], ed[5000000];

void insert(int len) {
	int p = 0;
	for(int i=1; i<=len; i++) {
		if(!trie[p][a[i]]) trie[p][a[i]] = ++tot;
		p = trie[p][a[i]];
		way[p]++;
	}
	ed[p]++;
}

int query(int len) {
	int p = 0, res = 0;
	for(int i=1; i<=len; i++) {
		if(!trie[p][a[i]]) return res;
		p = trie[p][a[i]];
		res += ed[p];
	}
	return res + way[p] - ed[p];
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++) {
		int x;
		scanf("%d", &x);
		for(int j=1; j<=x; j++)
			scanf("%d", &a[j]);
		insert(x);
	}
	for(int i=1; i<=m; i++) {
		int x;
		scanf("%d", &x);
		for(int j=1; j<=x; j++)
			scanf("%d", &a[j]);
		printf("%d\n", query(x));
	}
	return 0;
}

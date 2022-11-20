#include <bits/stdc++.h>
using namespace std;

struct node {
	int son[26], flag, fail;
}trie[1000010];
int n, tot, vis[1000010], ans;
char t[1000010], ansc[1000010];
char s[151][1000010];
queue<int> q;

void insert(char s[], int idx) {
	int p = 1, len = strlen(s+1);
	for(int i=1; i<=len; i++) {
		int c = s[i] - 'a';
		if(!trie[p].son[c]) trie[p].son[c] = ++tot;
		p = trie[p].son[c];
	}
	trie[p].flag = idx;
}

void getfail() {
	for(int i=0; i<26; i++) trie[0].son[i] = 1;
	q.push(1);
	trie[1].fail = 0;
	while(q.size()) {
		int p = q.front();
		q.pop();
		for(int i=0; i<26; i++) {
			int nx = trie[p].son[i];
			int f = trie[p].fail;
			if(!nx) {
				trie[p].son[i] = trie[f].son[i];
				continue;
			}
			trie[nx].fail = trie[f].son[i];
			q.push(nx);
		}
	}
}

void query(char s[]) {
	int p = 1, len = strlen(s+1);
	for(int i=1; i<=len; i++) {
		int c = s[i] - 'a';
		int k = trie[p].son[c];
		while(k > 1) {
			if(trie[k].flag) vis[trie[k].flag]++;
			k = trie[k].fail;
		}
		p = trie[p].son[c];
	}
}

void init() {
	for(int i=0; i<=tot; i++) {
		memset(trie[i].son, 0, sizeof(trie[i].son));
		trie[i].fail = trie[i].flag = 0;
	}
	for(int i=1; i<=n; i++) {
		vis[i] = 0;
	}
	tot = 1, ans = 0;
}

int main() {
	while(1) {
		scanf("%d", &n);
		if(!n) break;
		init();
		for(int i=1; i<=n; i++) {
			scanf("%s", s[i]+1);
			insert(s[i], i);
//			printf("OK\n");
		}
		scanf("%s", t+1);
		getfail();
		query(t);
		for(int i=1; i<=n; i++) {
			ans = max(ans, vis[i]);
		}
		printf("%d\n", ans);
		for(int i=1; i<=n; i++) {
			if(vis[i] == ans) {
				printf("%s\n", s[i]+1);
			}
		}
	}
	return 0;
}

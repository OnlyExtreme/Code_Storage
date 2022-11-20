#include <bits/stdc++.h>
using namespace std;

struct node {
	int son[26], flag, fail;
}trie[1000010];
int n, tot;
char s[1000010];
queue<int> q;

void insert(char s[]) {
	int p = 1, len = strlen(s+1);
	for(int i=1; i<=len; i++) {
		int c = s[i] - 'a';
		if(!trie[p].son[c]) trie[p].son[c] = ++tot;
		p = trie[p].son[c];
	}
	trie[p].flag++;
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

int query(char s[]) {
	int p = 1, res = 0, len = strlen(s+1);
	for(int i=1; i<=len; i++) {
		int nx = s[i] - 'a';
		int k = trie[p].son[nx];
		while(k > 1 && trie[k].flag != -1) {
			res += trie[k].flag, trie[k].flag = -1;
			k = trie[k].fail;
		}
		p = trie[p].son[nx];
	}
	return res;
}

int main() {
	tot = 1;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%s", s+1);
		insert(s);
	}
	getfail();
	for(int i=1; i<=tot; i++) {
		printf("Fail[%d] = %d\n", i, trie[i].fail);
	}
//	scanf("%s", s+1);
//	printf("%d\n", query(s));
	return 0;
}

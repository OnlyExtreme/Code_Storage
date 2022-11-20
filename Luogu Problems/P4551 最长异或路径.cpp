#include <bits/stdc++.h>
using namespace std;

int n;
int xorn[100010], trie[3200010][3], tot, ans;
vector<int> g[100010], w[100010];

void dfs(int cur, int fa) {
	for(int i=0; i<g[cur].size(); i++) {
		int nxt = g[cur][i], cst = w[cur][i];
		if(nxt == fa) continue;
		xorn[nxt] = xorn[cur] ^ cst;
		dfs(nxt, cur);
	}
}

void insert(int x) {
	int p = 0;
	for(int i=30; i>=0; i--) {
		int c = (x >> i) & 1;
		if(!trie[p][c]) trie[p][c] = ++tot;
		p = trie[p][c];
	}
}

int query(int x) {
	int p = 0, res = 0;
	for(int i=30; i>=0; i--) {
		int c = (x >> i) & 1;
		if(trie[p][!c]) 
			p = trie[p][!c], res += 1 << i;
		else p = trie[p][c];
	}
	return res;
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<n; i++) {
		int u, v, ww;
		scanf("%d %d %d", &u, &v, &ww);
		g[u].push_back(v);
		g[v].push_back(u);
		w[u].push_back(ww);
		w[v].push_back(ww);
	}
	dfs(1, 0);
	for(int i=1; i<=n; i++) insert(xorn[i]);
	for(int i=1; i<=n; i++) ans = max(ans, query(xorn[i]));
	printf("%d\n", ans);
	return 0;
}

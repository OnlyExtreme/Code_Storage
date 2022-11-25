#include <bits/stdc++.h>
using namespace std;

int n, m, s;
int fa[500010][21], dep[500010];
vector<int> g[500010];

void dfs(int x, int f) {
	fa[x][0] = f;
	dep[x] = dep[f] + 1;
	for (int i=1; i<=20; i++)
		fa[x][i] = fa[fa[x][i-1]][i-1];
	for (int i=0; i<g[x].size(); i++) {
		if(g[x][i] == f) continue;
		dfs(g[x][i], x);
	}
}

int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	int tmp = dep[y] - dep[x];
	for (int j=0; tmp; j++, tmp>>=1)
		if(tmp & 1) y = fa[y][j];
	if(y == x) return y;
	for (int j=20; j>=0 && y != x; j--) {
		if(fa[x][j] != fa[y][j]) {
			x = fa[x][j];
			y = fa[y][j];
		}
	}
	x = fa[x][0];
	return x;
}

int main() {
	scanf("%d %d %d", &n, &m, &s);
	for (int i=1; i<n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(s, 0);
	while (m--) {
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", lca(x, y));
	}
	return 0;
}

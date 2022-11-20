#include <bits/stdc++.h>
using namespace std;

int n, q;
int fa[100010], siz[100010], ans[100010];
struct edge {
	int u, v, w;
}g[100010];
struct aquery {
	int k, v, id;
}que[100010];

bool cmpedge(edge x, edge y) {
	return x.w > y.w;
}

bool cmpque(aquery x, aquery y) {
	return x.k > y.k;
}

void init() {
	for(int i=1; i<=n; i++) {
		fa[i] = i;
		siz[i] = 1;
	}
}

int get(int x) {
	return (x == fa[x]) ? x : fa[x] = get(fa[x]);
}

void merge(int x, int y) {
	int u = get(fa[x]), v = get(fa[y]);
	if(u == v) return;
	fa[v] = u;
	siz[u] += siz[v];
}

int main() {
	scanf("%d %d", &n, &q);
	init();
	for(int i=1; i<n; i++) {
		scanf("%d %d %d", &g[i].u, &g[i].v, &g[i].w);
	}
	for(int i=1; i<=q; i++) {
		scanf("%d %d", &que[i].k, &que[i].v);
		que[i].id = i;
	}
	sort(g+1, g+n, cmpedge);
	sort(que+1, que+q+1, cmpque);
	int cur = 1;
	for(int i=1; i<=q; i++) {
		while(cur <= n && que[i].k <= g[cur].w) {
			merge(g[cur].u, g[cur].v);
			cur++;
		}
		ans[que[i].id] = siz[get(que[i].v)] - 1;
	}
	for(int i=1; i<=q; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

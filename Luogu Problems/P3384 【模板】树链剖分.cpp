#include <bits/stdc++.h>
#define lc(k) a[k].c[0]
#define rc(k) a[k].c[1]
using namespace std;

int n, m, r, p;
int w[100010];
vector<int> g[100010];
int dep[100010], fa[100010], siz[100010], son[100010];
int nid[100010], nval[100010], top[100010], tot;

struct node {
	int l, r, c[2];
	long long sum, add;
}a[200010];
int cnt = 1;

void pushdown(int k) {
	if(a[k].add == 0) return;
	if(lc(k)) {
		a[lc(k)].add += a[k].add;
		a[lc(k)].sum += a[k].add * (a[lc(k)].r - a[lc(k)].l + 1);
	}
	if(rc(k)) {
		a[rc(k)].add += a[k].add;
		a[rc(k)].sum += a[k].add * (a[rc(k)].r - a[rc(k)].l + 1);
	}
	a[k].add = 0;
	return;
}

void update(int k) {
	a[k].sum = a[lc(k)].sum + a[rc(k)].sum;
}

void build(int k, int l, int r) {
	a[k].l = l, a[k].r = r;
	if(l == r) {
		a[k].sum += nval[l];
		return;
	}
	int mid = l + r >> 1;
	lc(k) = ++cnt;
	build(lc(k), l, mid);
	rc(k) = ++cnt;
	build(rc(k), mid+1, r);
	update(k);
}

void add(int k, int l, int r, int val) {
	if(a[k].l == l && a[k].r == r) {
		a[k].add += val;
		a[k].sum += val * (r - l + 1);
		return;
	}
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if(r <= mid) add(lc(k), l, r, val);
	else if(l > mid) add(rc(k), l, r, val);
	else {
		add(lc(k), l, mid, val);
		add(rc(k), mid+1, r, val);
	}
	update(k);
	return;
}

long long query(int k, int l, int r) {
	if(a[k].l == l && a[k].r == r)
		return a[k].sum;
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if(r <= mid) return query(lc(k), l, r);
	else if(l > mid) return query(rc(k), l, r);
	else return (query(lc(k), l, mid) + query(rc(k), mid+1, r));
}

void dfs1(int x, int f, int d) {
	dep[x] = d;
	fa[x] = f;
	siz[x] = 1;
	int maxson = -1;
	for(int i=0; i<g[x].size(); i++) {
		int y = g[x][i];
		if(y == f) continue;
		dfs1(y, x, d+1);
		siz[x] += siz[y];
		if(siz[y] > maxson)
			son[x] = y, maxson = siz[y];
	}
}

void dfs2(int x, int topf) {
	nid[x] = ++tot;
	nval[tot] = w[x];
	top[x] = topf;
	if(!son[x]) return;
	dfs2(son[x], topf);
	for(int i=0; i<g[x].size(); i++) {
		int y = g[x][i];
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

long long queryRange(int x, int y) {
	long long res = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res = 1ll * res + query(1, nid[top[x]], nid[x]) % p;
		res %= p;
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	res = 1ll * res + query(1, nid[x], nid[y]) % p;
	res %= p;
	return res;
}

void updateRange(int x, int y, int val) {
	val %= p;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		add(1, nid[top[x]], nid[x], val);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	add(1, nid[x], nid[y], val);
	return;
}

long long querySon(int x) {
	return query(1, nid[x], nid[x] + siz[x] - 1) % p;
}

void updateSon(int x, int val) {
	add(1, nid[x], nid[x] + siz[x] - 1, val % p);
}

int main() {
	scanf("%d %d %d %d", &n, &m, &r, &p);
	for(int i=1; i<=n; i++)
		scanf("%d", &w[i]);
	for(int i=1; i<n; i++) {
		int _x, _y;
		scanf("%d %d", &_x, &_y);
		g[_x].push_back(_y);
		g[_y].push_back(_x);
	}
	dfs1(r, 0, 1);
	dfs2(r, r);
	build(1, 1, n);
	while(m--) {
		int _opt, _x, _y, _z;
		scanf("%d", &_opt);
		if(_opt == 1) {
			scanf("%d %d %d", &_x, &_y, &_z);
			updateRange(_x, _y, _z);
		}
		else if(_opt == 2) {
			scanf("%d %d", &_x, &_y);
			printf("%lld\n", queryRange(_x, _y));
		}
		else if(_opt == 3) {
			scanf("%d %d", &_x, &_y);
			updateSon(_x, _y);
		}
		else {
			scanf("%d", &_x);
			printf("%lld\n", querySon(_x));
		}
	}
	return 0;
}

#include <bits/stdc++.h>
#define ls(k) a[k].c[0]
#define rs(k) a[k].c[1]
using namespace std;

int n, m, r, p;
vector<int> g[100010];
int w[100010];
int fa[100010], dep[100010], son[100010], siz[100010];
int nid[100010], nval[100010], top[100010], tot;
struct node {
	int l, r, c[2];
	long long sum, add;
} a[200010];
int cnt = 1;

void pushdown(int k) {
	if (!a[k].add) return;
	if(ls(k)) {
		a[ls(k)].add += a[k].add;
		a[ls(k)].sum += a[k].add * (a[ls(k)].r - a[ls(k)].l + 1);
	}
	if(rs(k)) {
		a[rs(k)].add += a[k].add;
		a[rs(k)].sum += a[k].add * (a[rs(k)].r - a[rs(k)].l + 1);
	}
	a[k].add = 0;
	return;
}

void update(int k) {
	a[k].sum = a[ls(k)].sum + a[rs(k)].sum;
	a[k].sum %= p;
}

void build(int k, int l, int r) {
	a[k].l = l, a[k].r = r;
	if(l == r) 
		return a[k].sum = 1ll * a[k].sum + nval[l], void();
	int mid = l + r >> 1;
	ls(k) = ++cnt;
	build(ls(k), l, mid);
	rs(k) = ++cnt;
	build(rs(k), mid + 1, r);
	update(k);
}

void add(int k, int l, int r, int val) {
	val %= p;
	if (a[k].l == l && a[k].r == r) {
		a[k].add = (a[k].add + 1ll * val) % p;
		a[k].sum += 1ll * val * (r - l + 1);
		a[k].sum %= p;
		return;
	}
	int mid = a[k].l + a[k].r >> 1;
	pushdown(k);
	if (r <= mid) add(ls(k), l, r, val);
	else if (l > mid) add(rs(k), l, r, val);
	else {
		add(ls(k), l, mid, val);
		add(rs(k), mid + 1, r, val);
	}
	update(k);
	return;
}

long long query(int k, int l, int r) {
	if (a[k].l == l && a[k].r == r) return a[k].sum;
	int mid = a[k].l + a[k].r >> 1;
	pushdown(k);
	if(r <= mid) return query(ls(k), l, r);
	else if(l > mid) return query(rs(k), l, r);
	else return (query(ls(k), l, mid) + query(rs(k), mid + 1, r)) % p;
}

void addRange(int x, int y, int val) {
	val %= p;
	while (top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		add(1, nid[top[x]], nid[x], val);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	add(1, nid[x], nid[y], val);
	return;
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

void addSon(int x, int val) {
	add(1, nid[x], nid[x] + siz[x] - 1, val % p);
}

long long querySon(int x) {
	return query(1, nid[x], nid[x] + siz[x] - 1) % p;
}

void dfs1(int x, int f, int d) {
	fa[x] = f;
	dep[x] = d;
	siz[x] = 1;
	int maxson = -1;
	for (int i = 0; i < g[x].size(); i++) {
		int y = g[x][i];
		if (y == f) continue;
		dfs1(y, x, d + 1);
		siz[x] += siz[y];
		if (siz[y] > maxson)
			maxson = siz[y], son[x] = y;
	}
}

void dfs2(int x, int topf) {
	nid[x] = ++tot;
	nval[tot] = w[x];
	top[x] = topf;
	if (!son[x]) return;
	dfs2(son[x], topf);
	for (int i = 0; i < g[x].size(); i++) {
		int y = g[x][i];
		if (y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

void prin(int k) {
	printf("now is in:%d l:%d r:%d sum:%lld add:%lld\n", k, a[k].l, a[k].r, a[k].sum, a[k].add);
	if (ls(k)) prin(ls(k));
	if (rs(k)) prin(rs(k));
}

int main() {
	scanf("%d %d %d %d", &n, &m, &r, &p);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i < n; i++) {
		int _x, _y;
		scanf("%d %d", &_x, &_y);
		g[_x].push_back(_y);
		g[_y].push_back(_x);
	}
	dfs1(r, 0, 1);
	dfs2(r, r);
	build(1, 1, n);
	
//		for (int i = 1; i <= n; i++) printf("fa[%d]:%d\n", i, fa[i]);
//		for (int i = 1; i <= n; i++) printf("dep[%d]:%d\n", i, dep[i]);
//		for (int i = 1; i <= n; i++) printf("siz[%d]:%d\n", i, siz[i]);
//		for (int i = 1; i <= n; i++) printf("son[%d]:%d\n", i, son[i]);
//		for (int i = 1; i <= n; i++) printf("top[%d]:%d\n", i, top[i]);
//		for (int i = 1; i <= n; i++) printf("nid[%d]:%d\n", i, nid[i]);
//		for (int i = 1; i <= n; i++) printf("nw[%d]:%d\n", i, nval[i]);
	
	while(m--) {
		
//		prin(1);
		
		int _op, _x, _y, _z;
		scanf("%d", &_op);
		if(_op == 1) {
			scanf("%d %d %d", &_x, &_y, &_z);
			addRange(_x, _y, _z);
		}
		else if(_op == 2) {
			scanf("%d %d", &_x, &_y);
			printf("%lld\n", queryRange(_x, _y));
		}
		else if(_op == 3) {
			scanf("%d %d", &_x, &_z);
			addSon(_x, _z);
		}
		else {
			scanf("%d", &_x);
			printf("%lld\n", querySon(_x));
		}
	}
	return 0;
}

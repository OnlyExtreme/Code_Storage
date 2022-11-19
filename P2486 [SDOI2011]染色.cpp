#include <bits/stdc++.h>
#define lc(k) a[k].c[0]
#define rc(k) a[k].c[1]
using namespace std;

int n, m, w[100010];
vector<int> g[100010];
int fa[100010], dep[100010], siz[100010], son[100010];
int top[100010], nid[100010], nw[100010], tot;
int qlc, qrc;

struct node {
	int l, r, c[2];
	int cl, cr, num, tag;
}a[500010];
int cnt = 1;

void pushdown(int k) {
	if(!a[k].tag) return;
	a[lc(k)].tag = a[rc(k)].tag = a[k].tag;
	a[lc(k)].num = a[rc(k)].num = 1;
	a[lc(k)].cl = a[lc(k)].cr = a[k].cl;
	a[rc(k)].cl = a[rc(k)].cr = a[k].cl;
	a[k].tag = 0;
	return;
}

void update(int k) {
	a[k].cl = a[lc(k)].cl;
	a[k].cr = a[rc(k)].cr;
	a[k].num = (a[lc(k)].cr == a[rc(k)].cl) ? a[lc(k)].num+a[rc(k)].num-1 : a[lc(k)].num+a[rc(k)].num;
	return;
}

void build(int k, int l, int r) {
	a[k].l = l, a[k].r = r;
	if(l == r) {
		a[k].cl = a[k].cr = nw[l];
		a[k].num = 1;
		return;
	}
	int mid = l + r >> 1;
	lc(k) = ++cnt;
	build(lc(k), l, mid);
	rc(k) = ++cnt;
	build(rc(k), mid+1, r);
	update(k);
	return;
}

void modify(int k, int l, int r, int val) {
	if(a[k].l == l && a[k].r == r) {
		a[k].num = a[k].tag = 1;
		a[k].cl = a[k].cr = val;
		return;
	}
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if(r <= mid) modify(lc(k), l, r, val);
	else if(l > mid) modify(rc(k), l, r, val);
	else {
		modify(lc(k), l, mid, val);
		modify(rc(k), mid+1, r, val);
	}
	update(k);
}

int query(int k, int l, int r, int ql, int qr) {
	if(a[k].l == ql) qlc = a[k].cl;
	if(a[k].r == qr) qrc = a[k].cr;
	if(a[k].l == l && a[k].r == r) return a[k].num;
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if(r <= mid) return query(lc(k), l, r, ql, qr);
	else if(l > mid) return query(rc(k), l, r, ql, qr);
	else return (a[lc(k)].cr == a[rc(k)].cl) ? query(lc(k), l, mid, ql, qr) + query(rc(k), mid+1, r, ql, qr) - 1 : query(lc(k), l, mid, ql, qr) + query(rc(k), mid+1, r, ql, qr);
}

void modifyRange(int x, int y, int val) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(1, nid[top[x]], nid[x], val);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	modify(1, nid[x], nid[y], val);
	return;
}

int queryRange(int x, int y) {
	int res = 0;
	int pos1 = 0, pos2 = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) {
			swap(x, y);
			swap(pos1, pos2);
		}
		res += query(1, nid[top[x]], nid[x], nid[top[x]], nid[x]);
		if(qrc == pos1) res--;
		pos1 = qlc, x = fa[top[x]];
	}
	if(dep[x] > dep[y]) {
		swap(x, y);
		swap(pos1, pos2);
	}
	res += query(1, nid[x], nid[y], nid[x], nid[y]);
	if(qlc == pos1) res--;
	if(qrc == pos2) res--;
	return res;
}

void prin(int k) {
	printf("now is in:%d l:%d r:%d cl:%d cr:%d num:%d tag:%d\n", k, a[k].l, a[k].r, a[k].cl, a[k].cr, a[k].num, a[k].tag);
	if (lc(k)) prin(lc(k));
	if (rc(k)) prin(rc(k));
}

void dfs1(int x, int f, int d) {
	fa[x] = f;
	dep[x] = d;
	siz[x] = 1;
	int maxson = -1;
	for(int i=0; i<g[x].size(); i++) {
		int y = g[x][i];
		if(y == f) continue;
		dfs1(y, x, d+1);
		siz[x] += siz[y];
		if(siz[y] > maxson)
			maxson = siz[y], son[x] = y;
	}
}

void dfs2(int x, int topf) {
	nid[x] = ++tot;
	nw[tot] = w[x];
	top[x] = topf;
	if(!son[x]) return;
	dfs2(son[x], topf);
	for(int i=0; i<g[x].size(); i++) {
		int y = g[x][i];
		if(y == fa[x] || y == son[x]) continue;
		dfs2(y, y);
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++)
		scanf("%d", &w[i]);
	for(int i=1; i<n; i++) {
		int _x, _y;
		scanf("%d %d", &_x, &_y);
		g[_x].push_back(_y);
		g[_y].push_back(_x);
	}
	getchar();
	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, 1, n);
	
//	prin(1);
//	for (int i = 1; i <= n; i++) printf("fa[%d]:%d\n", i, fa[i]);
//	for (int i = 1; i <= n; i++) printf("dep[%d]:%d\n", i, dep[i]);
//	for (int i = 1; i <= n; i++) printf("siz[%d]:%d\n", i, siz[i]);
//	for (int i = 1; i <= n; i++) printf("son[%d]:%d\n", i, son[i]);
//	for (int i = 1; i <= n; i++) printf("top[%d]:%d\n", i, top[i]);
//	for (int i = 1; i <= n; i++) printf("nid[%d]:%d\n", i, nid[i]);
//	for (int i = 1; i <= n; i++) printf("nw[%d]:%d\n", i, nw[i]);
	
	for(int i=1; i<=m; i++) {
		char op[10];
		int _a, _b, _c;
		scanf("%s", op);
		if(op[0] == 'C') {
			scanf("%d %d %d", &_a, &_b, &_c);
			modifyRange(_a, _b, _c);
		}
		else {
			scanf("%d %d", &_a, &_b);
			printf("%d\n", queryRange(_a, _b));
		}
		
//		prin(1);
		
	}
	return 0;
}

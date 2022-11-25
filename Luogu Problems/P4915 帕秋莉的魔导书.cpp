#include <bits/stdc++.h>
#define ls(k) a[k].c[0]
#define rs(k) a[k].c[1]
using namespace std;

const int inf = 2147483646;
int n, m;
struct segtree {
	int l, r, c[2];
	long long sum, add;
} a[8000005];
int cnt = 1;

void make(int k) {
	int l = a[k].l, r = a[k].r;
	int mid = l + r >> 1;
	if (!ls(k)) {
		ls(k) = ++cnt;
		a[ls(k)].l = l, a[ls(k)].r = mid;
		a[ls(k)].sum = a[ls(k)].add = 0;
	}
	if (!rs(k)) {
		rs(k) = ++cnt;
		a[rs(k)].l = mid + 1, a[rs(k)].r = r;
		a[rs(k)].sum = a[rs(k)].add = 0;
	}
	return;
}

void pushdown(int k) {
//	if (!a[k].add) return;
	if (1ll * ls(k) * rs(k) == 0) make(k);
	a[ls(k)].add += a[k].add;
	a[ls(k)].sum += a[k].add * (a[ls(k)].r - a[ls(k)].l + 1);
	a[rs(k)].add += a[k].add;
	a[rs(k)].sum += a[k].add * (a[rs(k)].r - a[rs(k)].l + 1);
	a[k].add = 0;
	return;
}

void update(int k) {
	a[k].sum = a[ls(k)].sum + a[rs(k)].sum;
	return;
}

void add(int k, int l, int r, int val) {
	if (a[k].l == l && a[k].r == r) {
		a[k].add += 1ll * val;
		a[k].sum += 1ll * val * (r - l + 1);
		return;
	}
//	if (1ll * ls(k) * rs(k) == 0) make(k);
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
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
	if (a[k].l == l && a[k].r == r)
		return a[k].sum;
//	if (1ll * ls(k) * rs(k) == 0) make(k);
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if (r <= mid) return query(ls(k), l, r);
	else if (l > mid) return query(rs(k), l, r);
	else return query(ls(k), l, mid) + query(rs(k), mid + 1, r);
}

int main() {
	a[1].l = 1, a[1].r = inf;
	a[1].add = a[1].sum = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int vv, ww;
		scanf("%d %d", &vv, &ww);
		add(1, vv, inf, ww);
	}
	for (int i = 1; i <= m; i++) {
		int op, vv, ww;
		scanf("%d %d %d", &op, &vv, &ww);
		if (op == 1)
			printf("%.4lf\n", (double)query(1, vv, ww) / (double)(ww - vv + 1));
		else
			add(1, vv, inf, ww);
	}
	return 0;
}

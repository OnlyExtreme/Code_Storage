#include <bits/stdc++.h>
#define int long long
#define lc(k) a[k].c[0]
#define rc(k) a[k].c[1]
using namespace std;

int num[100050];

struct segtree {
	int l, r, c[2];
	int add, sum;
} a[800050];
int cnt = 1;

void update(int k) {
	a[k].sum = a[lc(k)].sum + a[rc(k)].sum;
}

void pushdown(int k) {
	if(!a[k].add) return;
	a[lc(k)].add += 1ll * a[k].add;
	a[lc(k)].sum += 1ll * a[k].add * (a[lc(k)].r - a[lc(k)].l + 1);
	a[rc(k)].add += 1ll * a[k].add;
	a[rc(k)].sum += 1ll * a[k].add * (a[rc(k)].r - a[rc(k)].l + 1);
	a[k].add = 0;
}

void build(int k, int l, int r) {
	a[k].l = l, a[k].r = r;
	if(l == r) {
		a[k].sum += num[l];
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
		a[k].add += 1ll * val;
		a[k].sum += 1ll * val * (r - l + 1);
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

int query(int k, int l, int r) {
	if(a[k].l == l && a[k].r == r)
		return a[k].sum;
	pushdown(k);
	int mid = a[k].l + a[k].r >> 1;
	if(r <= mid) return query(lc(k), l, r);
	else if(l > mid) return query(rc(k), l, r);
	else {
		return query(lc(k), l, mid) + query(rc(k), mid+1, r);
	}
}

int n, m;

signed main() {
	scanf("%lld %lld", &n, &m);
	for(int i=1; i<=n; i++)
		scanf("%lld", &num[i]);
	build(1, 1, n);
	for(int i=1; i<=m; i++){
		int op;
		scanf("%lld", &op);
		if(op == 1){
			int x, y, k;
			scanf("%lld %lld %lld", &x, &y, &k);
			add(1, x, y, k); 
		}
		else{
			int x, y;
			scanf("%lld %lld", &x, &y);
			printf("%lld\n", query(1, x, y));
		}
	}
	return 0;
}

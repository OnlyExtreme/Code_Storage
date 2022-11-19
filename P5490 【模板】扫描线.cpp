#include <bits/stdc++.h>
#define lc(k) a[k].c[0]
#define rc(k) a[k].c[1]
using namespace std;

int n, val[5000000];
struct edge {
	int h, xl, xr, flag;
	bool operator < (const edge &tmp) const {
		return h < tmp.h;
	}
}e[5000000];
struct node {
	int l, r, c[2];
	long long sum, len;
}a[5000000];
int cnt = 1;

void update(int k) {
	if(a[k].sum) {
		a[k].len = val[a[k].r] - val[a[k].l];
		return;
	}
	a[k].len = a[lc(k)].len + a[rc(k)].len;
	return;
}

void build(int k, int l, int r) {
	a[k].len = a[k].sum = 0;
	if(a[k].l == a[k].r) return;
	int mid = a[k].l + a[k].r >> 1;
	if(!lc(k)) {
		lc(k) = ++cnt;
		build(lc(k), l, mid);
	}
	if(!rc(k)) {
		rc(k) = ++cnt;
		build(rc(k), mid+1, r);
	}
	return;
}

void modify(int k, long long l, long long r, int p) {
	if(val[a[k].l] == l && val[a[k].r] == r) {
		a[k].sum += p;
		update(k);
		return;
	}
	int mid = val[a[k].l] + val[a[k].r] >> 1;
	if(r <= mid) modify(lc(k), l, r, p);
	else if(l > mid) modify(rc(k), l, r, p);
	else {
		modify(lc(k), l, mid, p);
		modify(rc(k), mid+1, r, p);
	}
	update(k);
	return;
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		int xa, xb, ya, yb;
		scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
		val[2*i-1] = xa, val[2*i] = xb;
		e[2*i-1] = (edge){ya, xa, xb, 1};
		e[2*i] = (edge){yb, xa, xb, -1};
	}
	n <<= 1;
	sort(e+1, e+n+1);
	sort(val+1, val+n+1);
	int tot = unique(val+1, val+n+1) - val - 1;
	build(1, 1, tot-1);
	long long ans = 0;
	for(int i=1; i<n; i++) {
		modify(1, e[i].xl, e[i].xr, e[i].flag);
		ans += a[1].len * (e[i+1].h - e[i].h);
	}
	printf("%lld\n", ans);
	return 0;
}

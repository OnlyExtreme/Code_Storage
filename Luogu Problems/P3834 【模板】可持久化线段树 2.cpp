#include <bits/stdc++.h>
#define ls(k) a[k].c[0]
#define rs(k) a[k].c[1]
#define int long long
using namespace std;

int n, q, m, cnt = 1;
int num[2000010], rt[2000010];
const int MIN = -10000000000, MAX = 10000000000;

struct node {
	int c[2];
	int tot;
} a[8000010];

void update(int k) {
	a[k].tot = a[ls(k)].tot + a[rs(k)].tot;
}

void add(int h, int k, int l, int r, int pos, int val) {
	if (l == r) return a[k].tot += val, void();
	int mid = l + r >> 1;
	if (pos <= mid) {
		rs(k) = rs(h), ls(k) = ++cnt;
		a[ls(k)].tot = a[ls(h)].tot;
		add(ls(h), ls(k), l, mid, pos, val);
	}
	else {
		ls(k) = ls(h), rs(k) = ++cnt;
		a[rs(k)].tot = a[rs(h)].tot;
		add(rs(h), rs(k), mid + 1, r, pos, val);
	}
	update(k);
}

int query(int lft, int rig, int l, int r, int pos) {
	if (rig == 0) return 0;
	if (l == r) return 1;
	int mid = l + r >> 1;
	int tmptot = a[ls(rig)].tot - a[ls(lft)].tot;
	if (pos <= tmptot) return query(ls(lft), ls(rig), l, mid, pos);
	else return query(rs(lft), rs(rig), mid + 1, r, pos - tmptot);
}

signed main() {
	scanf("%lld %lld", &n, &q);
	for (int i=1; i<=n; i++)
		scanf("%d", &num[i]);
	rt[0] = 1;
	for (int i=1; i<=n; i++) {
		rt[i] = ++cnt;
		add(rt[i-1], rt[i], MIN, MAX, num[i], 1);
	}
	for (int i=1; i<=q; i++) {
		int l, r, k;
		scanf("%lld %lld %lld", &l, &r, &k);
		printf("%lld\n", query(rt[l-1], rt[r], MIN, MAX, k));
	}
	return 0;
}

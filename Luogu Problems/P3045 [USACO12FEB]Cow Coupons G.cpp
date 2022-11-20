#include <bits/stdc++.h>
#define int long long
using namespace std;

const double _DOWN = 0.996;
int n, k, m, ans;
struct node {
	int p, c;
}s[100000];
bool used[100000];
int usedcow[100000], nocow[100000];

bool cmp(node x, node y) {
	return (x.p + x.c) > (y.p + y.c);
}

int calc() {
	int num[100000];
	for(int i=1; i<=n; i++)
		num[i] = used[i] ? s[i].c : s[i].p;
	sort(num+1, num+n+1);
	int ans = 0;
	long long res = 0;
	for(int i=1; i<=n && res<=m; i++) {
		res += (long long)num[i];
		ans++;
	}
	if(res <= m) return ans;
	return ans - 1;
}

void sa() {
	double t = 10;
	while(t > 1e-2) {
		int x = rand() % k + 1;
		int y = rand() % (n-k) + 1;
		swap(usedcow[x], nocow[y]);
		used[usedcow[x]] = true;
		used[nocow[y]] = false;
		int cur = calc();
		int delta = cur - ans;
		if(delta > 0) ans = cur;
		else if(exp(-(double)delta / t) * RAND_MAX < rand()) {
			swap(usedcow[x], nocow[y]);
			used[usedcow[x]] = true;
			used[nocow[y]] = false;
		}
		t *= _DOWN;
	}
}

signed main() {
	srand(1919810+114514);
	scanf("%lld %lld %lld", &n, &k, &m);
	for(int i=1; i<=n; i++)
		scanf("%lld %lld", &s[i].p, &s[i].c);
	sort(s+1, s+n+1, cmp);
//	random_shuffle(s+1, s+n+1);
	for(int i=1; i<=k; i++) {
		usedcow[i] = i;
		used[i] = true;
	}
	for(int i=k+1; i<=n; i++) {
		nocow[i-k] = i;
		used[i] = false;
	}
	ans = calc();
	sa();
	printf("%lld\n", ans);
	return 0;
}

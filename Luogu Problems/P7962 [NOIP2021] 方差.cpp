#include <bits/stdc++.h>
#define int long long
using namespace std;

const double eps = 1e-4;
const double down = 0.996;
int n, ans = 1e9+10;
int a[10010], bac[10010];
mt19937 rnd(time(0));
uniform_int_distribution<> dist(0,1000000);
int st = clock();

int calc() {
	int res = 0, sum = 0;
	for(int i=1; i<=n; i++) {
		res += a[i] * a[i];
		sum += a[i];
	}
	res *= n;
	res -= sum * sum;
	return res;
}

void as() {
	double T = 1000;
	while(T > eps) {
		int x = rnd() % n + 1;
		int ori = a[x];
		if(x == 1 || x == n) continue;
		a[x] = a[x - 1] + a[x + 1] - a[x];
		double res = calc();
		if(res < ans) ans = res;
		else {
			if(exp((double)(ans - res) / T) < (double)dist(rnd) / 1000000)
				a[x] = ori;
			else ans = res;
		}
		T *= down;
	}
}

signed main() {
	scanf("%lld", &n);
	for(int i=1; i<=n; i++) {
		scanf("%lld", &a[i]);
		bac[i] = a[i];
	}
	for(int i=1; i<=1000; i++) {
		if(clock()-st >= 0.98 * CLOCKS_PER_SEC) break;
		for(int i=1; i<=n; i++) a[i] = bac[i];
		as();
	}
	printf("%d\n", ans);
	return 0;
}

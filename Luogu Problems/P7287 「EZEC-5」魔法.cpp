#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, a, b, s;
int num[100050];
int ans = -1;

bool check(int p, int m) {
	int nw = 0, res = 0;
	for (int i=1; i<=n; i++) {
		nw += p + num[i];
		res = max(res, nw);
		nw = max(nw, 0ll);
	}
	return res >= m;
}

signed main() {
	scanf("%lld %lld %lld %lld", &n, &a, &b, &s);
	for (int i=1; i<=n; i++)
		scanf("%lld", &num[i]);
	for (int i=0; i<=30; i++) {
		int l = 0, r = 2e9, t = 1 << i;
		while (l <= r) {
			int mid = l + r >> 1;
			if (check(mid, s / t + (s % t != 0))) {
				if (ans == -1) ans = mid * a + i * b;
				ans = min(ans, mid * a + i * b);
				r = mid - 1;
			}
			else l = mid + 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}

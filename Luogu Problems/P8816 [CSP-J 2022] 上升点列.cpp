#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, k, ans;
int dp[1000][1000];
struct node {
	int x, y;
	bool operator < (const node &t) const {
		if(x != t.x) return x < t.x;
		return y < t.y;
	}
} a[1000];

signed main() {
	scanf("%lld %lld", &n, &k);
	for (int i=1; i<=n; i++)
		scanf("%lld %lld", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1);
	for (int i=1; i<=n; i++) {
		dp[i][k] = 1;
		for (int j=0; j<=k; j++) {
			for (int t=1; t<i; t++) {
				if (a[t].x > a[i].x || a[t].y > a[i].y) continue;
				int dx = abs(a[i].x - a[t].x);
				int dy = abs(a[i].y - a[t].y);
				int dis = dx + dy - 1;
				if (j + dis > k) continue;
				dp[i][j] = max(dp[i][j], dp[t][j+dis] + dis + 1);
			}
		}
	}
	for (int i=1; i<=n; i++)
		for (int j=0; j<=k; j++)
			ans = max(ans, j + dp[i][j]);
	printf("%lld\n", ans);
	return 0;
}

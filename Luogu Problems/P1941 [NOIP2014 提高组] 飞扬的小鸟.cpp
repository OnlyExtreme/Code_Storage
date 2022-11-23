#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;

int n, m, k;
int up[20000], down[20000];
int dp[2][20010], cnt = 1, ans;
struct obstacle {
	int p, l, h;
	bool operator < (const obstacle &ob) const {
		return p < ob.p;
	}
}o[20000];

signed main() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for(int i=1; i<=n; i++)
		scanf("%lld %lld", &up[i], &down[i]);
	for(int i=1; i<=k; i++)
		scanf("%lld %lld %lld", &o[i].p, &o[i].l, &o[i].h);
	sort(o+1, o+k+1);
	for(int i=1; i<=m; i++)
		dp[0][i] = 0;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=m; j++)
			dp[i&1][j] = inf;
		for(int j=up[i]+1; j<=up[i]+m; j++)
			dp[i&1][j] = min(dp[(i&1)^1][j-up[i]]+1, dp[i&1][j-up[i]]+1);
		for(int j=m; j<=up[i]+m; j++)
			dp[i&1][m] = min(dp[i&1][m], dp[i&1][j]);
		for(int j=1; j<=m-down[i]; j++)
			dp[i&1][j] = min(dp[i&1][j], dp[(i&1)^1][j+down[i]]);
		if(i == o[cnt].p) {
			ans = inf;
			for(int j=0; j<=o[cnt].l; j++)
				dp[i&1][j] = inf;
			for(int j=m; j>=o[cnt].h; j--)
				dp[i&1][j] = inf;
			for(int j=1; j<=m; j++)
				ans = min(ans, dp[i&1][j]);
			if(ans == inf)
				return printf("0\n%d\n", cnt-1), 0;
			cnt++;
		}
	}
	ans = inf;
	for(int j=1; j<=m; j++)
		ans = min(ans, dp[n&1][j]);
	printf("1\n%d\n", ans);
	return 0;
}

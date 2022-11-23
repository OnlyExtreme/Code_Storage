#include <bits/stdc++.h>
using namespace std;

int s, n, m;
int a[500][500];
int dp[50000], ans = -1;

int main() {
	scanf("%d %d %d", &s, &n, &m);
	for (int i = 1; i <= s; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[j][i]);
	for (int i = 1; i <= n; i++)
		sort(a[i] + 1, a[i] + s + 1);
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 0; j--)
			for (int k = 1; k <= s; k++)
				if (j > a[i][k] * 2)
					dp[j] = max(dp[j], dp[j - a[i][k] * 2 - 1] + k * i);
	for (int i = 0; i <= m; i++)
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
	return 0;
}

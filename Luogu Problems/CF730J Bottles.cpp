#include <bits/stdc++.h>
using namespace std;

int n, dp[25000][200];
int k, t;
int suma, sumb;
struct bottle {
	int c, x;
	bool operator < (const bottle &bt) const {
		return c > bt.c;
	}
} a[500];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i].x);
		suma += a[i].x;
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].c);
	sort(a + 1, a + n + 1);
	while(sumb < suma) sumb += a[++k].c;
	memset(dp, 128, sizeof(dp));
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = sumb; j >= a[i].c; j--)
			for(int s = 1; s <= k; s++)
				dp[j][s] = max(dp[j][s], dp[j - a[i].c][s - 1] + a[i].x);
	for(int i = suma; i <= sumb; i++)
		t = max(t, dp[i][k]);
	printf("%d %d\n", k, suma - t);
	return 0;
}

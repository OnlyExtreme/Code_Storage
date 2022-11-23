#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int d, g, curlif, maxlif;
int ans;
int dp[1500][1500];
bool vis[1500][1500];
struct garbage {
	int t, f, h;
	bool operator < (const garbage &_t) const {
		return t < _t.t;
	}
} gar[1000];

int main() {
	scanf("%d %d", &d, &g);
	for (int i = 1; i <= g; i++)
		scanf("%d %d %d", &gar[i].t, &gar[i].f, &gar[i].h);
	sort(gar + 1, gar + g + 1);
	curlif = maxlif = 10;
	for (int i = 1; i <= g; i++) {
		curlif -= (gar[i].t - gar[i - 1].t);
		if (curlif < 0) break;
		curlif += gar[i].f;
		maxlif += gar[i].f;
	}
	ans = INF;
	vis[0][10] = true;
	for (int i = 1; i <= g; i++) {
		for (int j = maxlif; j >= 0; j--) {
			if (vis[i - 1][j + gar[i].t - gar[i - 1].t]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j + gar[i].t - gar[i - 1].t] + gar[i].h);
				vis[i][j] = true;
			}
			if (vis[i - 1][j + gar[i].t - gar[i - 1].t]) {
				dp[i][j + gar[i].f] = max(dp[i][j + gar[i].f], dp[i - 1][j + gar[i].t - gar[i - 1].t]);
				vis[i][j + gar[i].f] = true;
			}
			if (dp[i][j] >= d) {
				ans = gar[i].t;
				break;
			}
		}
		if (ans != INF) break;
	}
	if (ans == INF)
		printf("%d\n", maxlif);
	else
		printf("%d\n", ans);
	return 0;
}

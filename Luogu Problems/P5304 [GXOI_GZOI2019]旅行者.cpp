/*
  _____     _____
  |  __ \   |  __ \      _       _
  | |__) |  | |__) |   _| |_   _| |_
  |  _  /   |  ___|   |_  _|  |_  _|
  | | \ \   | |        |_|     |_|
  |_|  \_\  |_|
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int INF = 0x3f3f3f3f;
int t, n, m, k, ans;
int sp[100050];
int dis[100050];
struct edge {
	int x, y, z;
} e[500050];
struct node {
	int to, wi;
};
vector<node> g[100050];

void dij(int st) {
	memset(dis, 0x3f, sizeof(dis));
	dis[st] = 0;
	priority_queue<pair<int, int> > q;
	q.push(make_pair(0, st));
	while (q.size()) {
		int x = q.top().second;
		q.pop();
		for (int i = 0; i < g[x].size(); i++) {
			int y = g[x][i].to, z = g[x][i].wi;
			if (dis[y] > dis[x] + z) {
				dis[y] = dis[x] + z;
				q.push(make_pair(-dis[y], y));
			}
		}
	}
}

signed main() {
	scanf("%d", &t);
	while (t--) {
		ans = INF;
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= m; i++)
			scanf("%d %d %d", &e[i].x, &e[i].y, &e[i].z);
		for (int i = 1; i <= k; i++)
			scanf("%d", &sp[i]);

		for (int i = 0; (1 << i) <= k; i++) {
			for (int j = 1; j <= n + 2; j++)
				g[j].clear();
			for (int j = 1; j <= m; j++)
				g[e[j].x].push_back((node){e[j].y, e[j].z});
			for (int j = 1; j <= k; j++) {
				if (j & (1 << i))
					g[n + 1].push_back((node){sp[j], 0});
				else
					g[sp[j]].push_back((node){n + 2, 0});
			}
			dij(n + 1);
			if (dis[n + 2] != 0)
				ans = min(ans, dis[n + 2]);
			for (int j = 1; j <= n + 2; j++)
				g[j].clear();
			for (int j = 1; j <= m; j++)
				g[e[j].x].push_back((node){e[j].y, e[j].z});
			for (int j = 1; j <= k; j++) {
				if (j & (1 << i))
					g[sp[j]].push_back((node){n + 2, 0});
				else
					g[n + 1].push_back((node){sp[j], 0});
			}
			dij(n + 1);
			if (dis[n + 2] != 0)
				ans = min(ans, dis[n + 2]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

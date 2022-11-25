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

int n, m, s;
int dis[500010];
bool vis[500010];
priority_queue<pair<int, int> > q;
vector<int> g[500010], w[500010];

void dij() {
	memset(dis, 0x7f, sizeof(dis));
	dis[s] = 0;
	q.push(make_pair(0, s));
	while(q.size()) {
		int cur = q.top().second;
		q.pop();
		if(vis[cur]) continue;
		vis[cur] = 1;
		for (int i = 0; i < g[cur].size(); i++) {
			int nxt = g[cur][i], wi = w[cur][i];
			if(dis[nxt] > dis[cur] + wi) {
				dis[nxt] = dis[cur] + wi;
				q.push(make_pair(-dis[nxt], nxt));
			}
		}
	}
}

signed main() {
	scanf("%lld %lld %lld", &n, &m, &s);
	for (int i = 1; i <= m; i++) {
		int u, v, wi;
		scanf("%lld %lld %lld", &u, &v, &wi);
		g[u].push_back(v);
//		g[v].push_back(u);
		w[u].push_back(wi);
//		w[v].push_back(wi);
	}
	dij();
	for (int i = 1; i <= n; i++) {
		printf("%lld ", dis[i]);
	}
	return 0;
}

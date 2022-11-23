#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, k, ans;
int score[3000];
vector<int> g[3000];
bool vis[3000], valid[3000][3000];
vector<int> lar[3000];
int dis[3000];

void bfs(int x) {
	memset(dis, -1, sizeof(dis));
	queue<int> q;
	q.push(x);
	dis[x] = 0;
	while (q.size()) {
		int u = q.front();
		q.pop();
		if (u != x) {
			valid[x][u] = true;
			if (valid[1][u] && x != 1) {
				lar[x].push_back(u);
				sort(lar[x].begin(), lar[x].end(), [](int u, int v) {
					return score[u] > score[v];
				});
				if (lar[x].size() > 3) lar[x].pop_back();
			}
		}
		if (dis[u] > k) continue;
		for (int v : g[u]) {
			if (dis[v] != -1) continue;
			dis[v] = dis[u] + 1;
			q.push(v);
		}
	}
}

signed main() {
	scanf("%lld %lld %lld", &n, &m, &k);
	for (int i = 1; i < n; i++)
		scanf("%lld", &score[i + 1]);
	for (int i = 1; i <= m; i++) {
		int _x, _y;
		scanf("%lld %lld", &_x, &_y);
		g[_x].push_back(_y);
		g[_y].push_back(_x);
	}
	for (int i = 1; i <= n; i++) 
		bfs(i);
	for (int b = 2; b <= n; b++) {
		for (int c = 2; c <= n; c++) {
			if (valid[b][c]) {
				for (int a : lar[b]) {
					for (int d : lar[c]) {
						if (a != b && a != c && a != d && b != c && b != d && c != d)
							ans = max(ans, score[a] + score[b] + score[c] + score[d]);
					}
				}
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}

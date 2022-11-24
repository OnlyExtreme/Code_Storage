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

int n, m, q;
int val[500010], sum[500010], ori[500010], totsum;
int flag[500010], cursum;
struct edge {
	int x, y;
} e[500010];
struct query {
	int op, x, y;
} qu[500010];

signed main() {
	mt19937 rnd(time(0));
	scanf("%lld %lld", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%lld %lld", &e[i].x, &e[i].y);
	scanf("%lld", &q);
	for (int i = 1; i <= q; i++) {
		int _op, _x, _y;
		scanf("%lld", &_op);
		if (_op == 1 || _op == 3) scanf("%lld %lld", &_x, &_y);
		else scanf("%lld", &_x), _y = 0;
		qu[i] = (query){_op, _x, _y};
	}
	for (int t = 1; t <= 1; t++) {
		cursum = totsum = 0;
		memset(val, 0, sizeof(val));
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; i++)
			val[i] = rnd(), val[i] %= 100000, totsum += val[i];
//		if(t==2)for(int i=1;i<=n;i++)cout<<val[i]<<"-";
//		if(t==2)cout<<endl;
		for (int i = 1; i <= m; i++)
			sum[e[i].y] += val[e[i].x], ori[e[i].y] += val[e[i].x], cursum += val[e[i].x];
//		if(t==2)cout<<cursum<<endl;
//		if(t==2)cout<<cursum<<endl;
		for (int i = 1; i <= q; i++) {
			int op = qu[i].op, x = qu[i].x, y = qu[i].y;
			if (op == 1) cursum -= val[x], sum[y] -= val[x];
			else if (op == 2) cursum -= sum[x], sum[x] = 0;
			else if (op == 3) cursum += val[x], sum[y] += val[x];
			else if (op == 4) cursum += (ori[x] - sum[x]), sum[x] = ori[x];
			if (cursum == totsum) flag[i] |= (1 << t);
//			if(t==2)cout<<cursum<<" "<<totsum<<endl;
		}
	}
	for (int i = 1; i <= q; i++) {
//		printf("%d\n", flag[i]);
//		cout<<i<<"_"<<flag[i]<<endl;
		if (flag[i] == 2) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

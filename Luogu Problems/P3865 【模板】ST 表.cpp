#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
int lg[2000010], f[2000010][22];

void pre() {
	lg[1] = 0;
	lg[2] = 1;
	for (int i=3; i<=2000000; i++)
		lg[i] = lg[i / 2] + 1;
}

signed main() {
	scanf("%lld %lld", &n, &m);
	for (int i=1; i<=n; i++)
		scanf("%lld", &f[i][0]);
	pre();
	for (int j=1; j<=21; j++)
		for (int i=1; i+(1<<j)-1<=n; i++)
			f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	for (int i=1; i<=m; i++) {
		int l, r;
		scanf("%lld %lld", &l, &r);
		int s = lg[r - l + 1];
		printf("%lld\n", max(f[l][s], f[r-(1<<s)+1][s]));
	}
	return 0;
}

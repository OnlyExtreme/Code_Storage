#include <bits/stdc++.h>
using namespace std;

int n, ans = -1e9-10;
int a[500];
int f[500][500], g[500][500];
char c[500];

int main() {
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> c[i] >> a[i];
		a[n+i] = a[i], c[n+i] = c[i];
	}
	for(int i=1; i<=n*2; i++)
		for(int j=1; j<=n*2; j++)
			f[i][j] = -1e9-10, g[i][j] = 1e9+10;
	for(int i=1; i<=n*2; i++)
		f[i][i] = g[i][i] = a[i];
	for(int len=1; len<n; len++) {
		for(int l=1, r=l+len; r<=2*n; l++, r++) {
			for(int k=l; k<r; k++) {
				if(c[k+1] == 'x') {
					f[l][r] = max({f[l][r], f[l][k]*f[k+1][r], g[l][k]*g[k+1][r], f[l][k]*g[k+1][r], g[l][k]*f[k+1][r]});
					g[l][r] = min({g[l][r], g[l][k]*g[k+1][r], f[l][k]*f[k+1][r], f[l][k]*g[k+1][r], g[l][k]*f[k+1][r]});
				}
				else if(c[k+1] == 't') {
					f[l][r] = max(f[l][r], f[l][k]+f[k+1][r]);
					g[l][r] = min(g[l][r], g[l][k]+g[k+1][r]);
				}
			}
		}
	}
	for(int i=1; i<=n; i++)
		ans = max(ans, f[i][i+n-1]);
	printf("%d\n", ans);
	for(int i=1; i<=n; i++)
		if(f[i][i+n-1] == ans)
			printf("%d ", i);
	return 0;
}

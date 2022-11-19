#include <bits/stdc++.h>
using namespace std;

int n, ans1, ans2;
int a[200], dp1[200][200], dp2[200][200];
int suffix[200];

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		a[n+i] = a[i];
	}
	for(int i=1; i<=n*2; i++)
		suffix[i] = suffix[i-1] + a[i];
	for(int len=1; len<n; len++) {
		for(int l=1, r=l+len; r<n*2 && l<n*2; l++, r=l+len) {
			dp2[l][r] = 1e9+10;
			for(int k=l; k<r; k++) {
				dp1[l][r] = max(dp1[l][r], dp1[l][k] + dp1[k+1][r] + suffix[r] - suffix[l-1]);
				dp2[l][r] = min(dp2[l][r], dp2[l][k] + dp2[k+1][r] + suffix[r] - suffix[l-1]);
			}
		}
	}
	ans2 = 1e9+10;
	for(int i=1; i<=n; i++) {
		ans1 = max(ans1, dp1[i][i+n-1]);
		ans2 = min(ans2, dp2[i][i+n-1]);
	}
	printf("%d\n%d\n", ans2, ans1);
	return 0;
}

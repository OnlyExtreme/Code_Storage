#include <bits/stdc++.h>
using namespace std;

const int p = 19650827;
int n, a[1500];
int dp[2000][2000][2];

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		scanf("%d", &a[i]);
	for(int i=1; i<=n; i++)
		dp[i][i][0] = 1;
	for(int len=1; len<=n; len++) {
		for(int l=1, r=l+len; r<=n; l++, r++) {
			if(a[l] < a[l+1]) dp[l][r][0] += dp[l+1][r][0];
			if(a[l] < a[r]) dp[l][r][0] += dp[l+1][r][1];
			if(a[r] > a[r-1]) dp[l][r][1] += dp[l][r-1][1];
			if(a[r] > a[l]) dp[l][r][1] += dp[l][r-1][0];
			dp[l][r][0] %= p;
			dp[l][r][1] %= p;
		}
	}
	printf("%d\n", (dp[1][n][0] + dp[1][n][1]) % p);
	return 0;
}

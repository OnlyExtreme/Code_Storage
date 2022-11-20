#include <bits/stdc++.h>
using namespace std;

char s[100];
int n, dp[100][100][2];

bool check(int l, int r) {
	if((r-l+1) & 1) return false;
	int mid = l + r >> 1;
	for(int i=l; i<=mid; i++)
		if(s[i] != s[i+mid-l+1]) return false;
	return true;
}

int main() {
	scanf("%s", s+1);
	n = strlen(s+1);
	memset(dp, 0x3f, sizeof(dp));
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++)
			dp[i][j][0] = dp[i][j][1] = (j-i+1);
	for(int len=2; len<=n; len++) {
		for(int i=1, j=i+len-1; j<=n; i++, j++) {
			if(check(i, j)) dp[i][j][0] = min(dp[i][j][0], dp[i][(i+j)/2][0]+1);
			for(int k=i; k<j; k++)
				dp[i][j][0] = min(dp[i][j][0], dp[i][k][0]+j-k);
			for(int k=i; k<j; k++)
				dp[i][j][1] = min(dp[i][j][1], min(dp[i][k][0], dp[i][k][1])+min(dp[k+1][j][0], dp[k+1][j][1])+1);
		}
	}
	printf("%d\n", min(dp[1][n][0], dp[1][n][1]));
	return 0;
}

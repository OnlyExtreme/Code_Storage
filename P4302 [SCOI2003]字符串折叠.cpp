#include <bits/stdc++.h>
using namespace std;

char s[150];
int dp[150][150], n;
int digits[150];

bool check(int l, int r, int len) {
	for(int i=l; i<=r; i++)
		if(s[i] != s[(i-l)%len+l])
			return false;
	return true;
}

int main() {
	scanf("%s", s+1);
	n = strlen(s+1);
	for(int i=1; i<=9; i++) digits[i] = 1;
	for(int i=10; i<=99; i++) digits[i] = 2;
	digits[100] = 3;
	memset(dp, 0x3f, sizeof(dp));
	for(int i=1; i<=n; i++) dp[i][i] = 1;
	for(int len=2; len<=n; len++) {
		for(int i=1, j=i+len-1; j<=n; i++, j++) {
			for(int k=i; k<j; k++)
				dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]);
			for(int k=i; k<j; k++) {
				int lenl = k - i + 1;
				if(len % lenl) continue;
				if(check(i, j, lenl))
					dp[i][j] = min(dp[i][j], dp[i][k] + 2 + digits[len/lenl]);
			}
		}
	}
	printf("%d\n", dp[1][n]);
	return 0;
}

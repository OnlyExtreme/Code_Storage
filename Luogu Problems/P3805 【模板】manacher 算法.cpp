#include <bits/stdc++.h>
using namespace std;

int len, m;
int cnt, p[22000010];
int mid, maxr, ans;
char c[22000010], s[22000010];

int main() {
	scanf("%s", c+1);
	len = strlen(c+1);
	s[++cnt] = '~';
	s[++cnt] = '#';
	for(int i=1; i<=len; i++) {
		s[++cnt] = c[i];
		s[++cnt] = '#';
	}
	s[++cnt] = '!';
	for(int i=2; i<cnt; i++) {
		if(i <= maxr)
			p[i] = min(p[mid * 2 - i], maxr - i + 1);
		else p[i] = 1;
		while(s[i-p[i]] == s[i+p[i]]) ++p[i];
		if(i + p[i] > maxr)
			maxr = i + p[i] - 1, mid = i;
		ans = max(ans, p[i]);
	}
	printf("%d", ans - 1);
	return 0;
}

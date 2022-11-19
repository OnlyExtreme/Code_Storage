#include <bits/stdc++.h>
using namespace std;

const int p = 1e9 + 7;
int nxt[1000010], num[1000010];
int t;
long long ans;
char s[1000010];

int main() {
	scanf("%d", &t);
	while(t--) {
		ans = 1;
		num[1] = 1;
		scanf("%s", s+1);
		int len = strlen(s+1);
		for(int i=2, j=0; i<=len; i++) {
			while(j && s[i] != s[j+1])
				j = nxt[j];
			if(s[i] == s[j+1])
				j++;
			nxt[i] = j;
			num[i] = num[j] + 1;
		}
		for(int i=2, j=0; i<=len; i++) {
			while(j && s[i] != s[j+1])
				j = nxt[j];
			if(s[i] == s[j+1])
				j++;
			while((j<<1) > i)
				j = nxt[j];
			ans = 1ll * ans * (num[j] + 1) % p;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

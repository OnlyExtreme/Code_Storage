#include <bits/stdc++.h>
using namespace std;

int n, k, a[1000010];
int q[1000010];
int fr, bc;

int main() {
	scanf("%d %d", &n, &k);
	for (int i=1; i<=n; i++)
		scanf("%d", &a[i]);
	if (k == 1) {
		for (int i=1; i<=n; i++)
			printf("%d ", a[i]);
		printf("\n");
		for (int i=1; i<=n; i++)
			printf("%d ", a[i]);
		return 0;
	}
	
	q[++fr] = 1;
	for (int i=2; i<=n; i++) {
		while(fr >= bc && q[bc] + k <= i) bc++;
		while(fr >= bc && a[q[fr]] >= a[i]) fr--;
		q[++fr] = i;
		if(i >= k) printf("%d ", a[q[bc]]);
	}
	printf("\n");
	memset(q, 0, sizeof(q));
	fr = bc = 0;
	q[++fr] = 1;
	for (int i=2; i<=n; i++) {
		while(fr >= bc && q[bc] + k <= i) bc++;
		while(fr >= bc && a[q[fr]] <= a[i]) fr--;
		q[++fr] = i;
		if(i >= k) printf("%d ", a[q[bc]]);
	}
	return 0;
}

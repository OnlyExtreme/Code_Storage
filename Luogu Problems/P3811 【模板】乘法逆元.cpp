#include <bits/stdc++.h>
using namespace std;

long long n, p;

long long qp(long long a, long long b) {
	long long res = 1 % p, x = a;
	for (; b; b >>= 1) {
		if(b & 1) res = res * x % p;
		x = x * x % p;
	}
	return res;
}

int main() {
	scanf("%lld %lld", &n, &p);
	for (int i=1; i<=n; i++)
		printf("%lld\n", qp(i, p-2));
	return 0;
}

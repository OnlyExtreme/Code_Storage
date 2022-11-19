#include <bits/stdc++.h>
using namespace std;

const double _DOWN = 0.996;
int n, m;
int a[50];
double avg, ans, gr[50];

double calc() {
	double res = 0.00, minn;
	int idx;
	for(int i=1; i<=m; i++)
		gr[i] = 0;
	for(int i=1; i<=n; i++) {
		minn = 1e9;
		for(int j=1; j<=m; j++)
			if(gr[j] < minn)
				minn = gr[j], idx = j;
		gr[idx] += a[i];
	}
	for(int i=1; i<=m; i++)
		res += (avg - gr[i]) * (avg - gr[i]);
	return res;
}

void as() {
	double t = 1000.0;
	int p1, p2;
	while(t > 1e-2) {
		p1 = rand() % n + 1;
		p2 = rand() % n + 1;
		if(p1 == p2) continue;
		swap(a[p1], a[p2]);
		double res = calc();
		if(res < ans) ans = res;
		else if(exp((ans - res) / t) * RAND_MAX < (double)rand())
			swap(a[p1], a[p2]);
		t *= _DOWN;
	}
}

int main() {
	srand((unsigned)time(0));
	scanf("%d %d", &n, &m);
	avg = 0.00;
	ans = 1e9;
	for(int i=1; i<=n; i++) {
		scanf("%d", &a[i]);
		avg += (double)a[i];
	}
	avg /= m;
	for(int i=1; i<=20; i++) {
		random_shuffle(a+1, a+n+1);
		as();
	}
	printf("%.2f\n", sqrt(ans / m));
	return 0;
}

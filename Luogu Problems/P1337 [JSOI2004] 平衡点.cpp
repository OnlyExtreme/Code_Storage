#include <bits/stdc++.h>
using namespace std;

const double _DOWN = 0.996;
int n;
struct node {
	int x, y, w;
}obj[3000];
double ansx, ansy, answ;
double energy(double x, double y) {
	double r = 0, dx, dy;
	for(int i=1; i<=n; i++) {
		dx = x - obj[i].x;
		dy = y - obj[i].y;
		r += sqrt(dx * dx + dy * dy) * obj[i].w;
	}
	return r;
}

void sa() {
	double t = 3000;
	while(t > 1e-15) {
		double rx = ansx + (rand() * 2 - RAND_MAX) * t;
		double ry = ansy + (rand() * 2 - RAND_MAX) * t;
		double rw = energy(rx, ry);
		double delta = rw - answ;
		if(delta < 0) {
			ansx = rx;
			ansy = ry;
			answ = rw;
		}
		else if(exp(-delta / t) * RAND_MAX > rand()) {
			ansx = rx;
			ansy = ry;
		}
		t *= _DOWN;
	}
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d %d %d", &obj[i].x, &obj[i].y, &obj[i].w);
		ansx += obj[i].x;
		ansy += obj[i].y;
	}
	ansx /= n;
	ansy /= n;
	answ = energy(ansx, ansy);
	for(int i=1; i<=3; i++) {
		sa();
	}
	printf("%.3lf %.3lf\n", ansx, ansy);
	return 0;
}

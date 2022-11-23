#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

int n;
long long k, ans;
tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> bbt;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int opt;
		scanf("%lld %lld", &opt, &k);
		if (opt == 1) bbt.insert((k << 20) + i);
		if (opt == 2) bbt.erase(bbt.lower_bound(k << 20));
		if (opt == 3) printf("%lld\n", bbt.order_of_key(k << 20) + 1);
		if (opt == 4) ans = *bbt.find_by_order(k - 1), printf("%lld\n", ans >> 20);
		if (opt == 5) ans = *--bbt.lower_bound(k << 20), printf("%lld\n", ans >> 20);
		if (opt == 6) ans = *bbt.upper_bound((k << 20) + n), printf("%lld\n", ans >> 20);
	}
	return 0;
}

#include <iostream>
#include <cstring> 

using namespace std;

int C;
int N;

int cache[101][101];
int ans;
const int MOD = 10000000;
int Poly(int n, int first) {
	if (n == first) return 1;

	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;
	for (int second = 1; second <= n - first; ++second) {
		int temp = first + second - 1;
		temp *= Poly(n - first, second);
		temp %= MOD;
		ret += temp;
		ret %= MOD;
	}
	return ret;
}

void _init() {
	memset(cache, -1, sizeof(cache));
	ans = 0;
}
int main() {
	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		cin >> N;

		for (int i = 1; i <= N; i++) {
			ans += Poly(N, i);
			ans %= MOD;
		}
		cout << ans << endl;
	}
}
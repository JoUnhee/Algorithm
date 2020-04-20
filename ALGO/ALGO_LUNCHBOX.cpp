#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int C, n;
vector<pair<int, int>> q;

bool cmp(pair<int, int> A, pair<int, int> B) {
	return A.first < B.first;
}
void _init() {
	q.clear();
}
void _input() {
	cin >> n;

	q.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> q[i].second;
	}
	for (int i = 0; i < n; i++) {
		cin >> q[i].first;
		q[i].first *= -1;
	}
}
void solve() {

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		_input();

		sort(q.begin(), q.end(), cmp);

		int sum = 0;
		int ans = 0;

		for (int i = 0; i < q.size(); i++) {
			sum += q[i].second;

			ans = max(ans, sum - q[i].first);
		}

		cout << ans << endl;
	}
}
int main() {
	
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
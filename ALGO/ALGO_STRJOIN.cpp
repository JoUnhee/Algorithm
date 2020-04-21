#include <iostream>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>> q;
int C, N;

void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int num; cin >> num;
		q.push(num);
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_input();
		int ans = 0;
		while (q.size() > 1) {
			int a = q.top();
			q.pop();
			int b = q.top();
			q.pop();
			ans += a + b;
			q.push(a + b);
		}

		q.pop();

		cout << ans << endl;
	}
	
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
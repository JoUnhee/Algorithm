#include<iostream>
#include<algorithm>

using namespace std;

int W[11][11];
int ret = 987654321;

bool check[11];

int N;
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> W[i][j];
		}
	}
}
void DFS(int first, int cur, int sum, int cnt) {

	if (cnt == N && first == cur) {
		ret = min(ret, sum);
		return;
	}

	for (int next = 0; next < N; next++) {
		if (W[cur][next] == 0) continue;
		if (check[next]) continue;

		sum += W[cur][next];
		check[next] = true;
		if (ret >= sum) {
			DFS(first, next, sum, cnt + 1);
		}

		sum -= W[cur][next];
		check[next] = false;
	}
}
void solve() {
	for (int i = 0; i < N; i++) {
		DFS(i, i, 0, 0);
	}

	cout << ret << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	solve();
}
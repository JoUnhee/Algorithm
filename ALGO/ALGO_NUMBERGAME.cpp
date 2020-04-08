#include<iostream>
#include<algorithm>
#include <cstring>
using namespace std;
int C;
int N;
const int INF = -987654321;

int board[50];
int cache[50][50];

void _input() {
	
	cin >> N;

	for (int i = 0; i < N; i++) cin >> board[i];
}
void _init() {

	memset(board, 0, sizeof(board));
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			cache[i][j] = INF;
		}
	}
}
int game(int left, int right) {
	if (left > right) return 0;

	int& ret = cache[left][right];

	if (ret != INF) return ret;

	ret = max(board[left] - game(left + 1, right), board[right] - game(left, right - 1));

	if (right - left + 1 >= 2) {
		ret = max(ret, -game(left + 2, right));
		ret = max(ret, -game(left, right - 2));
	}
	return ret;
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;
	for (int t = 1; t <= C; t++) {
		_init();
		_input();
		int ans = game(0, N - 1);

		cout << ans << endl;
	}
}
int main() {

	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	solve();
}
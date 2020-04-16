#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

int n;
int ans;

int visit[500][500];
int map[500][500];

int dx[4] = { -1, 0, 1 ,0 };
int dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}
int DFS(int x, int y) {
	int& ret = visit[y][x];

	if (ret != -1) return ret;

	ret = 1;

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (!isInside(nx, ny)) continue;
		if (map[y][x] >= map[ny][nx]) continue;

		ret = max(ret, DFS(nx, ny) + 1);
	}
	return ret;
}
void _init() {
	memset(map, 0, sizeof(map));
	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
			visit[i][j] = -1;
	ans = 0;
}
void _input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}
void solve() {

	_init();
	_input();
	

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans = max(ans, DFS(i, j));
		}
	}

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
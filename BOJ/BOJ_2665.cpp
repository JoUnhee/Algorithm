#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;


int n;
int ans;

int map[50][50];
int visit[50][50];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };



void _init() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			visit[i][j] = 987654321;
		}
	}
	memset(map, 0, sizeof(map));
	ans = 987654321;
}
void _input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp - '0';
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}
void BFS() {
	queue<pair<int, int>> q;

	q.push({ 0,0 });
	visit[0][0] = 0;

	while (!q.empty()) {
		int x = q.front().second;
		int y = q.front().first;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!isInside(nx, ny)) continue;

			if (map[ny][nx] == 1) {
				if (visit[ny][nx] > visit[y][x]) {
					visit[ny][nx] = visit[y][x];
					q.push({ ny,nx });
				}
			}
			else if (map[ny][nx] == 0) {
				if (visit[ny][nx] > visit[y][x] + 1) {
					visit[ny][nx] = visit[y][x] + 1;
					q.push({ ny,nx });
				}
			}

		}
	}
	
	return ;
}

void solve() {

	_init();
	_input();

	BFS();
	ans = visit[n - 1][n - 1];
	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
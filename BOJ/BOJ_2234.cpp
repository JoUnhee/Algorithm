#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int N, M;

bool visit[50][50];
int map[50][50];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < M;
}
int BFS(int c, int r) {
	queue<pair<int, int>> q;
	q.push({ c,r });
	visit[r][c] = true;
	int cnt = 1;
	while (!q.empty()) {
		
		int x = q.front().first;
		int y = q.front().second;

		q.pop();

		int bit = 1;

		for (int i = 0; i < 4; i++) {
			if (!(map[y][x] & bit)) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!isInside(nx, ny)) continue;
				if (!visit[ny][nx]) {
					cnt++;
					q.push({ nx,ny });
					visit[ny][nx] = true;
				}
			}
			bit <<= 1;
		}
	}
	return cnt;
}
void solve() {
	int cnt = 0;
	int section = 0;
	int ret = 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j]) continue;
			cnt = max(cnt, BFS(j, i));
			section++;
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int wall = 1; wall <= 8; wall <<= 1) {
				if ((map[i][j] & wall)) {
					memset(visit, 0, sizeof(visit));
					map[i][j] -= wall;
					ret = max(ret, BFS(j, i));
					map[i][j] += wall;
				}
			}
		}
	}
	cout << section << endl;
	cout << cnt << endl;
	cout << ret << endl;
}
void _input() {
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	solve();

}

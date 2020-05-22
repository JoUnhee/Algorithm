#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define INF 987654321
using namespace std;

typedef struct Cam {
	int x;
	int y;
	int type;

	Cam(int _x, int _y, int _type) : x(_x), y(_y), type(_type) {}
};

int N, M;
int map[8][8];
int sz ;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

vector<Cam> camera;
int ans;
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] >= 1 && map[i][j] <= 5) {
				camera.push_back(Cam(j, i, map[i][j]));
			}
		}
	}
}
void _init() {
	memset(map, 0, sizeof(map));
	camera.clear();

	ans = INF;
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void Fill(int idx, int dir, bool visit[][8]) {
	int type = camera[idx].type;
	int x = camera[idx].x;
	int y = camera[idx].y;

	if (type == 1) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];

		while (isInside(nx, ny) && map[ny][nx] != 6) visit[ny][nx] = true, nx += dx[dir], ny += dy[dir];
	}
	else if (type == 2) {
		for (int i = 0; i < 2; i++) {
			int nx = x + dx[(dir + (2 * i)) % 4];
			int ny = y + dy[(dir + (2 * i)) % 4];

			while (isInside(nx, ny) && map[ny][nx] != 6) visit[ny][nx] = true, nx += dx[(dir + 2 * i) % 4], ny += dy[(dir + 2 * i) % 4];
		}
	}
	else if (type == 3) {
		for (int i = 0; i < 2; i++) {
			int nx = x + dx[(dir + i) % 4];
			int ny = y + dy[(dir + i) % 4];

			while (isInside(nx, ny) && map[ny][nx] != 6) visit[ny][nx] = true, nx += dx[(dir + i) % 4], ny += dy[(dir + i) % 4];
		}
	}
	else if (type == 4) {
		for (int i = 0; i < 4; i++) {
			if (i == (dir + 2) % 4) continue;
			int nx = x + dx[i];
			int ny = y + dy[i];

			while (isInside(nx, ny) && map[ny][nx] != 6) visit[ny][nx] = true, nx += dx[i], ny += dy[i];
		}
	}
	else if (type == 5) {
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			while (isInside(nx, ny) && map[ny][nx] != 6) visit[ny][nx] = true, nx += dx[i], ny += dy[i];
		}
	}
}

int simul(int state) {

	int cnt = 0;
	bool visit[8][8];
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < sz; i++) {

		int dir = (state >>(i*2)) & 3;
		Fill(i, dir, visit);

	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visit[i][j] && map[i][j] == 0) cnt++;
		}
	}
	return cnt;
}
void DFS(int idx, int state) {
	if (idx == sz) {
		ans = min(ans, simul(state));
		return;
	}

	for (int i = 0; i < 4; i++) {

		int tState = state | (i << (idx * 2));
		DFS(idx+1,tState);
		
		if (camera[idx].type == 2) i += 2;
		else if (camera[idx].type == 5) i += 3;
	}
}
void solve() {
	_init();
	_input();

	sz = camera.size();
	DFS(0, 0);

	cout << ans << endl;
}
int main() {

	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
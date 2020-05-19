#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
int map[50][50];
bool visit[50][50];

int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int x, y, dir;
int ans;

void _init() {
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	ans = 0;
}
void _input() {
	cin >> N >> M;

	cin >> y >> x >> dir;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void solve() {

	_init();
	_input();

	while(1){
		//현 위치 청소 시도
		if (map[y][x] == 0 && !visit[y][x]) visit[y][x] = true;
	
		int ndir = dir;
		bool check = false;

		for (int i = 0; i < 4; i++) {
			ndir = (ndir + 3) % 4;

			int nx = x + dx[ndir];
			int ny = y + dy[ndir];

			if (!isInside(nx, ny)) continue;
			if (map[ny][nx] == 1) continue;
			if (visit[ny][nx]) continue;

			// 청소가 가능하다면 회전 후 전진
			x = nx;
			y = ny;
			dir = ndir;
			check = true;
			break;
		}

		//청소 했는지 판단
		if (check) continue;

		int bdir = (dir + 2) % 4;
		int bx = x + dx[bdir];
		int by = y + dy[bdir];

		if (!isInside(bx, by) || map[by][bx] == 1) break;

		x = bx;
		y = by;
	}
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (visit[i][j]) ans++;
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

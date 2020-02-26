#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef struct point {
	int x;
	int y;
	int cnt;
	int dir;

	point(int _x, int _y, int _cnt, int _dir) : x(_x), y(_y), cnt(_cnt), dir(_dir) {}
};
int sx, sy;
int ex, ey;
int ret;
int W, H;

int MAP[101][101];
int visit[101][101];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,-1,1 };

void init() {

	ret = 987654321;
	sx = sy = ex = ey = -1;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			visit[i][j] = 987654321;
		}
	}

	memset(MAP, 0, sizeof(MAP));


}
void input() {
	cin >> W >> H;

	init();
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			char tmp;
			cin >> tmp;

			if (tmp == '.') MAP[i][j] = 0;
			else if (tmp == 'C') {
				MAP[i][j] = 2;
				if (sx == -1) {
					sx = j, sy = i;
				}
				else {
					ex = j, ey = i;
				}
			}
			else if (tmp == '*') {
				MAP[i][j] = 1;
			}
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < W && y >= 0 && y < H;
}
void solve() {

	input();

	queue<point> q;
	for (int i = 0; i < 4; i++) {
		q.push(point(sx, sy, 0, i));
	}
	visit[sy][sx] = 0;

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		int dir = q.front().dir;

		q.pop();

		for (int tDir = 0; tDir < 4; tDir++) {
			int nx = x + dx[tDir];
			int ny = y + dy[tDir];
			int ncnt = cnt;

			if (!isInside(nx, ny)) continue;
			if (MAP[ny][nx] == 1) continue;
			if (tDir != dir) ncnt = cnt + 1;
			if (visit[ny][nx] >= ncnt) {
				visit[ny][nx] = ncnt;
				q.push(point(nx, ny, ncnt, tDir));
			}
		}
	}

	ret = visit[ey][ex];

	cout << ret << endl;
	return;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}


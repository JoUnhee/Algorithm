#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

typedef struct info {
	int x;
	int y;
	int dir;

	info(int _x, int _y, int _dir) : x(_x), y(_y), dir(_dir) {}

};
int N, M;
int map[101][101];

bool visit[101][101][5];

int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0, 0,0,1,-1};

int sx, sy, sdir;
int ex, ey, edir;

bool isInside(int x, int y) {
	return x > 0 && x <= N && y > 0 && y <= M;
}
int change_dir(int dir,int which_way) {
	if (which_way == 0) {	//¿ÞÂÊ
		if (dir == 1) return 4;
		else if (dir == 2) return 3;
		else if (dir == 3) return 1;
		else if (dir == 4) return 2;
	}
	else if (which_way == 1) {	//¿ÞÂÊ
		if (dir == 1) return 3;
		else if (dir == 2) return 4;
		else if (dir == 3) return 2;
		else if (dir == 4) return 1;
	}
	else return dir;
}
int solve() {

	queue<info> q;

	q.push(info(sx, sy, sdir));
	visit[sy][sx][sdir] = true;
	int cnt = 0;
	while (!q.empty()) {
		int sz = q.size();

		for (int s = 0; s < sz; s++) {
			int x = q.front().x;
			int y = q.front().y;
			int dir = q.front().dir;

			q.pop();

			if (x == ex && y == ey && dir == edir) {
				return cnt;
			}
			int nx, ny, ndir;

			for (int k = 1; k <= 3; k++) {
				nx = x + dx[dir] * k;
				ny = y + dy[dir] * k;

				if (!isInside(nx, ny)) break;
				if (visit[ny][nx][dir]) continue;
				if (map[ny][nx] == 1) break;

				visit[ny][nx][dir] = true;
				q.push(info(nx, ny, dir));
			}
			for (int i = 0; i < 2; i++) {
				ndir = change_dir(dir, i);

				if (visit[y][x][ndir]) continue;
				visit[y][x][ndir] = true;
				q.push(info(x, y, ndir));
			}
		}
		cnt++;
	}
	return -1;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> M >> N;

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
	
	cin >> sy >> sx >> sdir;
	cin >> ey >> ex >> edir;

	cout << solve() << endl;

}


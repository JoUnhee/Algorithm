#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;
typedef struct info {
	int x;
	int y;
	int dir;

	info(int _x, int _y, int _dir) : x(_x), y(_y), dir(_dir) {}
};

int R, C;
char map[25][25];

char type[7] = { '|' ,'-','+','1','2','3','4' };

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

int sx, sy;
int sdir;
int rx, ry;
char rtype;

vector<info> zero;

bool isInside(int x, int y) {
	return x >= 0 && x < C && y >= 0 && y < R;
}
void _init() {
	memset(map, 0, sizeof(map));
	rx = ry = rtype = 0;
}
void _input() {
	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];

			if (map[i][j] == 'M') sx = j, sy = i;
		}
	}
}
bool canGo(int dir, char type) {
	if (type == '+') return true;
	else if (type == 'Z') return true;

	if (dir == 0) return type == '|' || type == '1' || type == '4';
	if (dir == 1) return type == '|' || type == '2' || type == '3';
	if (dir == 2) return type == '-' || type == '1' || type == '2';
	if (dir == 3) return type == '-' || type == '3' || type == '4';
	return false;
}
int changeDir(int dir, char type) {
	if (type == '+' || type == '-' || type == '|') return dir;
	else {
		if (type == '1') return (dir + 3) % 4;
		else if (type == '2') return (dir + 2) % 4;
		else if (type == '3') return (dir + 1) % 4;
		else if (type == '4') return (dir + 2) %4 ;
	}
}
bool simul(int tx,int ty, int tdir, bool flag) {
	queue<info> q;
	bool visit[25][25];

	memset(visit, 0, sizeof(visit));

	q.push(info(tx, ty, tdir));

	visit[ty][tx] = true;
	
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int dir = q.front().dir;

		q.pop();

		if (map[y][x] == 'Z') return true;

		int nx = x + dx[dir];
		int ny = y + dy[dir];
		
		if (!isInside(nx, ny)) continue;
		if (flag && map[ny][nx] == '.') zero.push_back(info(nx, ny, dir));


		if (!canGo(dir, map[ny][nx])) continue;
		int ndir = changeDir(dir, map[ny][nx]);

		if (map[ny][nx] == '+') {
			q.push(info(nx, ny, ndir));
			visit[ny][nx] = true;
		}
		else {
			if (visit[ny][nx]) continue;

			q.push(info(nx, ny, ndir));
			visit[ny][nx] = true;
		}
		
	}

	return false;
}
void solve() {

	_init();
	_input();

	for (int i = 0; i < 4; i++) {
		int x = sx + dx[i];
		int y = sy + dy[i];

		if (!isInside(x, y)) continue;
		zero.clear();
		sdir = i;
		simul(sx, sy, sdir, true);

		for (int i = 0; i < zero.size(); i++) {

			int x = zero[i].x;
			int y = zero[i].y;
			int dir = zero[i].dir;

			for (int i = 0; i < 7; i++) {
				if (!canGo(dir, type[i])) continue;
				map[y][x] = type[i];
				bool flag = simul(sx, sy, sdir, false);
				map[y][x] = '.';
				if (!flag) continue;

				rx = x + 1;
				ry = y + 1;
				rtype = type[i];

				return;
			}
		}
		
	}



}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);


	solve();

	cout << ry << ' ' << rx<< ' ' << rtype << endl;
}
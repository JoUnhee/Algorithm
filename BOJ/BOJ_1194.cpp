#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

typedef struct info {
	int x;
	int y;
	int state;

	info(int _x, int _y, int _state) : x(_x), y(_y), state(_state) {}
};
int N, M;
int sx, sy;
char map[50][50];
bool visit[50][50][1 << 6];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

int change(char obj) {
	if (obj == 'a' || obj == 'A') {
		return 1 << 5;
	}
	if (obj == 'b'|| obj == 'B') {
		return 1 << 4;
	}
	if (obj == 'c'|| obj == 'C') {
		return 1 << 3;
	}
	if (obj == 'd' || obj == 'D') {
		return 1 << 2;
	}
	if (obj == 'e' || obj == 'E') {
		return 1 << 1;
	}
	if (obj == 'f' || obj == 'F') {
		return 1;
	}
}
bool canGo(int state, char obj) {
	return state & (change(obj));
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];

			if (map[i][j] == '0') {
				sx = j, sy = i;
			}
		}
	}
}
int solve() {
	int t = 0;
	queue<info> q;
	q.push(info(sx, sy, 0));
	visit[sy][sx][0] = true;

	while (!q.empty()) {
		int sz = q.size();

		for (int s = 0; s < sz; s++) {
			int x = q.front().x;
			int y = q.front().y;
			int state = q.front().state;

			q.pop();

			if (map[y][x] == '1') {
				return t;
			}


			for (int i = 0; i < 4; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				int nstate = state;
				if (!isInside(nx, ny)) continue;
				
				if (map[ny][nx] >= 'a' && map[ny][nx] <= 'f') {
					nstate |= change(map[ny][nx]);
				}

				if (visit[ny][nx][nstate]) continue;
				if (map[ny][nx] == '#') continue;
				else if (map[ny][nx] >= 'A' && map[ny][nx] <= 'F') {
					if (!canGo(nstate, map[ny][nx])) continue;
				}
				
				visit[ny][nx][nstate] = true;
				q.push(info(nx, ny, nstate));
				
			}
		}
		t++;
	}

	return -1;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	int ret = solve();

	cout << ret << endl;

}
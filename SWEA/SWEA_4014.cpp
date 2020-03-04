#include<cstring>
#include<iostream>

using namespace std;

int T, N, X;
int map[20][20];
bool visit[20];
int ret;
bool isInside(int x) {
	return x >= 0 && x < N;
}
void _input() {
	cin >> N >> X;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
void _init() {
	ret = 0;
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
}
void putSlope(int x,int dir) {
	if (dir == -1) {
		for (int nx = x - X + 1; nx <= x; nx++) visit[nx] = true;
	}
	else if (dir == 1) for (int nx = x + 1; nx <= x + X; nx++) visit[nx] = true;
}
bool canPutSlopeHo(int x, int y, int dir) {
	int cnt = 0;
	int h = 0;
	if (dir == -1) {
		h = map[y][x];
		for (int nx = x - X + 1; nx <= x; nx++) {
			if (!isInside(nx)) return false;
			if (map[y][nx] != h) return false;
			bool vCusor = visit[nx];
			if (vCusor) return false;
			cnt++;
		}
	}
	else if (dir == 1) {
		h = map[y][x+1];
		for (int nx = x + 1; nx <= x+X; nx++) {
			if (!isInside(nx)) return false;
			if (map[y][nx] != h) return false;
			bool vCusor = visit[nx];
			if (vCusor) return false;
			cnt++;
		}
	}
	
	return true;

}

bool canPutSlopeVer(int x, int y, int dir) {
	int cnt = 0;
	int h = 0;
	if (dir == -1) {
		h = map[y][x];
		for (int ny = y - X + 1; ny <= y; ny++) {
			if (!isInside(ny)) return false;
			if (map[ny][x] != h) return false;
			bool vCusor = visit[ny];
			if (vCusor) return false;
			cnt++;
		}
	}
	else if (dir == 1) {
		h = map[y+1][x];
		for (int ny = y + 1; ny <= y+X; ny++) {
			if (!isInside(ny)) return false;
			if (map[ny][x] != h) return false;
			bool vCusor = visit[ny];
			if (vCusor) return false;
			cnt++;
		}
	}
	
	return true;

}
void checkHo() {
	for (int y = 0; y < N; y++) {
		memset(visit, 0, sizeof(visit));
		for (int x = 0; x < N; x++) {
			int h = map[y][x];

			if (x == N - 1) {
				ret++;
				break;
			}

			int nx = x + 1;
			int nh = map[y][nx];
			int gap = h - nh;

			if (gap == 0) continue;
			else if (abs(gap) == 1) {
				if (canPutSlopeHo(x, y, gap)) {
					putSlope(x,gap);
					continue;
				}
				else break;
			}
			else break;
		}
	}
}
void checkVer() {
	for (int x = 0; x < N; x++) {
		memset(visit, 0, sizeof(visit));
		for (int y = 0; y < N; y++) {
			int h = map[y][x];

			if (y == N - 1) {
				ret++;
				break;
			}

			int ny = y + 1;
			int nh = map[ny][x];
			int gap = h - nh;

			if (gap == 0) continue;
			else if (abs(gap) == 1) {
				if (canPutSlopeVer(x, y, gap)) {
					putSlope(y, gap);
					continue;
				}
				else break;
			}
			else break;
		}
	}


}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		_init();
		_input();

		checkHo();
		checkVer();
		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
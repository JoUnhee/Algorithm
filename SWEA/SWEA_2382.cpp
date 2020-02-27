#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef struct Cell {
	int cnt;
	int dir;
	int maxNum;
};

int T;
int N, M, K;

Cell MAP[2][101][101];
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,-1,1,0,0 };

int ret;

void init() {
	ret = 0;
	memset(MAP, 0, sizeof(MAP));
}

void _input() {
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++) {
		int r, c, cnt, dir;
		cin >> r >> c >> cnt >> dir;
		
		MAP[0][r][c].cnt = cnt;
		MAP[0][r][c].dir = dir;
	}
}
int changeDir(int dir) {
	if (dir == 1) return 2;
	else if (dir == 2) return 1;
	else if (dir == 3) return 4;
	else if (dir == 4) return 3;
}
void simul() {
	int cur = 0;

	for (int m = 0; m < M; m++) {
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				Cell& now = MAP[cur][y][x];

				if (now.cnt == 0) continue;

				int dir = now.dir;
				int cnt = now.cnt;


				int nx = x + dx[dir];
				int ny = y + dy[dir];

				Cell& next = MAP[1 - cur][ny][nx];

				if (nx == 0 || nx == N - 1 || ny == 0 || ny == N - 1) {
					next.cnt = cnt / 2;
					next.dir = changeDir(dir);
					next.maxNum = cnt;
				}
				else {
					if (next.cnt > 0) {
						if (next.maxNum < cnt) {
							next.maxNum = cnt;
							next.dir = dir;
						}
						next.cnt += cnt;
					}
					else if (next.cnt == 0) {
						next.dir = dir;
						next.cnt = cnt;
						next.maxNum = cnt;
					}
				}

				now.cnt = 0;
				now.dir = 0;
				now.maxNum = 0;

			}
		}
		cur = 1 - cur;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (MAP[cur][i][j].cnt == 0) continue;
			ret += MAP[cur][i][j].cnt;
		}
	}

}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();
		_input();

		simul();

		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
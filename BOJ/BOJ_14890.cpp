#include <cstring>
#include <cstdio>
#include <iostream>

#define MAXN 100
using namespace std;

int N;
int L;

int map[MAXN][MAXN];
bool visit[MAXN];

int ans;

void _init() {
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	ans = 0;
}

void _input() {
	cin >> N >> L;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void Hcheck() {
	for (int r = 0; r < N; r++) {

		memset(visit, 0, sizeof(visit));
		bool flag = true;
		for (int x = 0; x < N - 1 && flag; x++) {

			int nx = x + 1;
			int cur = map[r][x];
			int next = map[r][nx];

			if (cur < next) {

				for (int l = 0; l < L; l++) {
					if (!isInside(x - l, r) || visit[x - l] || cur != map[r][x - l]) {
						flag = false;
						break;
					}
				}

				if (flag) {
					for (int l = 0; l < L; l++) {
						visit[x - l] = true;
					}
				}
			}

			else if (cur > next) {
				for (int l = 0; l < L; l++) {
					if (!isInside(nx + l, r) || visit[nx + l] || next != map[r][nx + l]) {
						flag = false;
						break;
					}
				}

				if (flag) {
					for (int l = 0; l < L; l++) visit[nx + l] = true;
				}
			}
			else continue;
		}
		if (flag) ans++;

	}
}
void Vcheck() {
	for (int c = 0; c < N; c++) {

		memset(visit, 0, sizeof(visit));
		bool flag = true;

		for (int y = 0; y < N - 1 && flag; y++) {
			int ny = y + 1;
			int cur = map[y][c];
			int next = map[ny][c];

			if (cur < next) {
				for (int l = 0; l < L; l++) {
					if (!isInside(c, y - l) || visit[y - l] || cur != map[y - l][c]) {
						flag = false;
						break;
					}
				}

				if (flag) {
					for (int l = 0; l < L; l++) {
						visit[y - l] = true;
					}
				}
			}
			else if (cur > next) {
				for (int l = 0; l < L; l++) {
					if (!isInside(c, ny + l) || visit[ny + l] || next != map[ny+l][c]) {
						flag = false;
						break;
					}
				}

				if (flag) {
					for (int l = 0; l < L; l++) {
						visit[ny + l] = true;
					}
				}
			}
			else continue;
		}
		if (flag) ans++;
	}
}
void solve() {

	_init();
	_input();

	Hcheck();
	Vcheck();

	cout << ans << endl;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
int map[20][20];
int ans = 0;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void _init() {
	memset(map, 0, sizeof(map));
	ans = 0;
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
void move(int dir, int(*B)[20]) {

	bool visit[20][20];
	memset(visit, 0, sizeof(visit));
	// 왼쪽
	if (dir == 0) {

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int cur = B[i][j];
				B[i][j] = 0;
				int x = j;
				if (cur == 0) continue;

				while (isInside(x + dx[dir], i) && B[i][x + dx[dir]] == 0) x += dx[dir];

				if (!isInside(x + dx[dir], i) || B[i][x + dx[dir]] != cur) {
					B[i][x] = cur;
				}
				else if (B[i][x + dx[dir]] == cur) {
					if (!visit[i][x + dx[dir]]) {
						visit[i][x + dx[dir]] = true;
						B[i][x + dx[dir]] += cur;
					}
					else {
						B[i][x] = cur;
					}
				}
			}
		}
	}
	// 위쪽
	else if (dir == 1) {
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				int cur = B[i][j];
				B[i][j] = 0;
				int y = i;
				if (cur == 0) continue;

				while (isInside(j, y + dy[dir]) && B[y + dy[dir]][j] == 0) y += dy[dir];

				if (!isInside(j, y + dy[dir]) || B[y + dy[dir]][j] != cur) {
					B[y][j] = cur;
				}
				else if (B[y + dy[dir]][j] == cur) {
					if (!visit[y + dy[dir]][j]) {
						visit[y + dy[dir]][j] = true;
						B[y + dy[dir]][j] += cur;
					}
					else {
						B[y][j] = cur;
					}
				}
			}
		}
	}
	//오른쪽
	else if (dir == 2) {
		for (int i = 0; i < N; i++) {
			for (int j = N - 1; j >= 0; j--) {
				int cur = B[i][j];
				B[i][j] = 0;
				int x = j;
				if (cur == 0) continue;

				while (isInside(x + dx[dir], i) && B[i][x + dx[dir]] == 0) x += dx[dir];

				if (!isInside(x + dx[dir], i) || B[i][x + dx[dir]] != cur) {
					B[i][x] = cur;
				}
				else if (B[i][x + dx[dir]] == cur) {
					if (!visit[i][x + dx[dir]]) {
						visit[i][x + dx[dir]] = true;
						B[i][x + dx[dir]] += cur;
					}
					else {
						B[i][x] = cur;
					}
				}
			}
		}
	}
	//아래
	else if (dir == 3) {
		for (int j = 0; j < N; j++) {
			for (int i = N - 1; i >= 0; i--) {
				int cur = B[i][j];
				B[i][j] = 0;
				int y = i;
				if (cur == 0) continue;

				while (isInside(j, y + dy[dir]) && B[y + dy[dir]][j] == 0) y += dy[dir];

				if (!isInside(j, y + dy[dir]) || B[y + dy[dir]][j] != cur) {
					B[y][j] = cur;
				}
				else if (B[y + dy[dir]][j] == cur) {
					if (!visit[y + dy[dir]][j]) {
						visit[y + dy[dir]][j] = true;
						B[y + dy[dir]][j] += cur;
					}
					else {
						B[y][j] = cur;
					}
				}
			}
		}
	}
}
void cpyArr(int dst[][20], int obj[][20]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dst[i][j] = obj[i][j];
		}
	}
	return;
}
int cntMax(int B[][20]) {
	int ret = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ret = max(ret, B[i][j]);
		}
	}
	return ret;
}
void DFS(int cnt, int B[][20]) {

	if (cnt >= 5) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		int TB[20][20];
		cpyArr(TB, B);
		move(i, TB);

		ans = max(ans, cntMax(TB));

		DFS(cnt + 1, TB);
	}
}
void solve() {

	_init();
	_input();

	DFS(0, map);
	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
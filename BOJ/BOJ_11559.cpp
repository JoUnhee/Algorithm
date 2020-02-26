#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

char MAP[12][6];
int visit[12][6];
int dx[4] = { -1, 0 , 1, 0 };
int dy[4] = { 0 , -1, 0 , 1 };
int ret;

void input() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> MAP[i][j];
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < 6 && y >= 0 && y < 12;
}
void BFS(int x, int y) {

	queue<pair<int, int>> q;
	queue<pair<int, int>> tq;
	tq.push({ x,y });
	q.push({ x,y });
	visit[y][x] = 1;
	int cnt = 0;
	while (!q.empty()) {
		
		int r = q.front().second;
		int c = q.front().first;
		char cur = MAP[r][c];

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = c + dx[i];
			int ny = r + dy[i];

			if (isInside(nx, ny) && MAP[ny][nx] == cur && visit[ny][nx] == 0) {
				q.push({ nx, ny });
				visit[ny][nx] = 1;
				tq.push({ nx,ny });
			}
		}

	}

	if (tq.size() >= 4) {
		while (!tq.empty()) {
			int r = tq.front().second;
			int c = tq.front().first;

			visit[r][c] = 2;
			tq.pop();
		}
	}



}
void Move() {
	for (int i = 10; i >= 0; i--) {
		for (int j = 0; j < 6; j++) {
			if (MAP[i][j] == '.') continue;

			int ty = i;

			while (ty <= 11 && MAP[ty+1][j] == '.') ty++;

			if(MAP[ty][j] == '.'){
				MAP[ty][j] = MAP[i][j];
				MAP[i][j] = '.';
			}
		}
	}
}
bool bomb() {

	bool flag = false;

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (MAP[i][j] == '.') continue;
			if (visit[i][j] >= 1) continue;
			BFS(j,i);
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (MAP[i][j] == '.') continue;
			if (visit[i][j] == 2) {
				flag = true;
				MAP[i][j] = '.';
			}
		}
	}

	if (flag) {
		Move();
	}
	return flag;
}
void solve() {
	ret = 0;
	while (1) {
		memset(visit, 0, sizeof(visit));

		if (bomb()) ret++;
		else break;
	}

	cout << ret << endl;

}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();
}
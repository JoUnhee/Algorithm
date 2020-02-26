#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

int ret;
char MAP[8][8];
int dx[9] = { 1,-1,0,0,1,1,-1,-1,0 };
int dy[9] = { 0, 0, 1, -1,1,-1,1,-1,0 };

bool isInside(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}
void move() {

	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			if (i == 0)	MAP[i][j] = '.';
			else MAP[i][j] = MAP[i - 1][j];
		}
	}

}
void input() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> MAP[i][j];
		}
	}
}

void solve() {
	queue<pair<int, int>> q;
	q.push({ 0,7 }); // 시작 위치 가장 왼쪽 아래
	int time = 0;
	while (!q.empty()) {
	
		int sz = q.size();
		if (time >= 8) {
			ret = 1;
			break;
		}
		for(int s = 0 ; s< sz; s++){
			int x = q.front().first;
			int y = q.front().second;
			
			q.pop();
			if (MAP[y][x] == '#') continue;
			if (y == 0 && x == 7) {
				ret = 1;
				break;
			}

			for (int i = 0; i < 9; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (!isInside(nx, ny)) continue;
				if (MAP[ny][nx] == '#') continue;
				q.push({ nx,ny });
			}
		}

		move();
		time++;
	}
	cout << ret << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();
	return 0;
}
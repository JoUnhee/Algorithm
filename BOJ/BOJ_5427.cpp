#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

int w, h;
int T;
int ret;

char map[1000][1000];
bool visit[1000][1000];
bool visit2[1000][1000];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

queue<pair<int, int>> fire;
queue<pair<int, int>> q;

bool escape(int x, int y) {
	return x < 0 || x >= w || y < 0 || y >= h;
}
void _input() {

	cin >> w >> h;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];

			if (map[i][j] == '*') fire.push({ i,j });
			else if (map[i][j] == '@') q.push({ i,j });
		}
	}
}
void init() {
	ret = 0;
	while (!fire.empty()) fire.pop();
	while (!q.empty()) q.pop();
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	memset(visit2, 0, sizeof(visit2));
}
bool isInside(int x, int y) {
	return x >= 0 && x < w && y>= 0 && y < h;
}
void spread() {
	int sz = fire.size();

	for (int s = 0; s < sz; s++) {
		int x = fire.front().second;
		int y = fire.front().first;

		fire.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!isInside(nx, ny)) continue;
			if (map[ny][nx] == '#'||map[ny][nx] == '*') continue;
			if (visit[ny][nx]) continue;
			visit[ny][nx] = true;
			map[ny][nx] = '*';
			fire.push({ ny,nx });

		}
	}

}
bool BFS() {
	int sz = q.size();

	for (int s = 0; s < sz; s++) {
		int x = q.front().second;
		int y = q.front().first;

		q.pop();

		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (escape(nx, ny)) return true;
			if (map[ny][nx] == '*' || map[ny][nx] == '#') continue;
			if (visit2[ny][nx]) continue;
			visit2[ny][nx] = true;
			map[ny][nx] = '@';
			q.push({ ny,nx });
		}
	}
	return false;
}
void solve() {
	
	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();

		_input();
		int time = 0;
		bool flag = false;
		while (!q.empty()) {
			spread();

			if (BFS()) {
				cout << time+1 << endl;
				flag = true;
				break;
			}
			time++;
		}

		if(!flag) cout << "IMPOSSIBLE" << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>

#define MAXN 50

using namespace std;

int N, L, R;
int map[MAXN][MAXN];
int visit[MAXN][MAXN];
int ans;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0, -1, 0, 1 };

bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void _input() {
	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
		}
	}
}
void _init() {

	memset(visit, -1, sizeof(visit));
	memset(map, 0, sizeof(map));
	ans = 0;
}
int BFS(int _x, int _y, int flag) {
	queue<pair<int, int>> q;

	q.push({ _x,_y });
	visit[_y][_x] = flag;
	int sum = map[_y][_x];
	int cnt = 1;
	while (!q.empty()) {
		
		int x = q.front().first;
		int y = q.front().second;
		int cur = map[y][x];

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if (!isInside(nx, ny)) continue;
			if (visit[ny][nx] != -1) continue;
			
			int obj = abs(map[ny][nx]-cur);
			
			if (obj < L || obj >R) continue;

			visit[ny][nx] = flag;
			cnt++;
			sum += map[ny][nx];

			q.push({ nx,ny });

		}
	}

	if (cnt == 1) return cnt;

	int avg = sum / cnt;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == flag) map[i][j] = avg;
		}
	}

	return cnt;
}
void printMap() {
	printf("---------------------\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}
void printVisit() {
	printf("---------------------\n");

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3d", visit[i][j]);
		}
		printf("\n");
	}
}
void solve() {

	_init();
	_input();

	bool flag = false;

	while (!flag) {
		memset(visit, -1, sizeof(visit));
		int now = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {

				if (visit[y][x] != -1) continue;
				int cnt = BFS(x,y,now++);

				if (cnt == 1) {
					flag |= false;
				}
				else if(cnt > 1) flag = true;

			}
		}
		//printMap();
		//printVisit();
		if (flag) flag = false, ans++;
		else break;
	}

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
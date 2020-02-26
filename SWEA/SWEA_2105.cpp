#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int T;
int N;
int ret;
int dstX, dstY;
int map[20][20];
bool visit[101];

int dx[4] = { -1,1,1,-1 };
int dy[4] = { 1,1,-1,-1 };
void setUp() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}
void init() {
	ret = 0;
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	dstX = dstY = -1;
}
bool canGo(int nDir, int dir,int cnt) {
	if (dir == 0) {
		if (cnt != 0)
			return nDir == 0 || nDir == 1;
		else return nDir == 0;
	}
	if (dir == 1) {
		return nDir == 1 || nDir == 2;
	}
	if (dir == 2) {
		return nDir == 2 || nDir == 3;
	}
	if (dir == 3) {
		return nDir == 3;
	}

	return false;
}
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void DFS(int x, int y, int dir, int cnt) {

	if (x == dstX && y == dstY && cnt != 0) {
		ret = max(ret, cnt);
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (!canGo(i, dir,cnt)) continue;
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!isInside(nx, ny)) continue;
			if (visit[map[ny][nx]]) continue;
			//if (i == 2 && ny == y) continue;
			//if (dir == 2 && i == 3 && nx < dstX) continue;
			visit[map[ny][nx]] = true;
			DFS(nx, ny,i, cnt + 1);
			visit[map[ny][nx]] = false;
		}
	}

}
void print() {
	printf("-----------------------------------------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();
		_input();
		//print();

		for (int i = 0; i < N - 2; i++) {
			//if (ret >= (N - i) * 2) break;
			for (int j = 1; j < N - 1; j++) {
				
				dstX = j, dstY = i;
				DFS(j, i, 0, 0);
			}
		}

		if (ret == 0) ret = -1;
		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	
	setUp();
	solve();
}
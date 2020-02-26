#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

int T;
int N;
int K;
int ret = 0;
int maxH = 0;
int map[8][8];
bool visit[8][8];
int dx[4] = { -1, 0 , 1 , 0 };
int dy[4] = { 0 , 1 , 0 , -1 };

void init() {
	memset(map, 0, sizeof(map));
	memset(visit, 0, sizeof(visit));
	ret = 0;
	maxH = 0;
}
void _input() {
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (maxH < map[i][j]) maxH = map[i][j];
		}
	}


}
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
int DFS(int x, int y, bool flag) {
	
	if (visit[y][x]) return 0;
	visit[y][x] = true;

	int ret = 1;
	int H = map[y][x];

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (isInside(nx, ny) && !visit[ny][nx]) {
			if (map[ny][nx] < H) {
				ret = max(ret, DFS(nx, ny, flag) + 1);
			}
			else if(map[ny][nx] >= H && !flag){
				for (int k = 1; k <= K; k++) {
					if (map[ny][nx] - k < H) {
						map[ny][nx] -= k;
						ret = max(ret, DFS(nx, ny, true) + 1);
						map[ny][nx] += k;
					}
				}
			}
		}
	}
	visit[y][x] = false;
	return ret;
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		init();
		_input();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] != maxH) continue;
				ret = max(ret,DFS(j, i, false));
			}
		}

		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
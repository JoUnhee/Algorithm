#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 21
#define MAXT 101
using namespace std;

int T, N, ans;
int stx, sty;

bool Visit[MAXT];
int MAP[MAXN][MAXN];

int dx[4] = { 1,-1,-1,1 };
int dy[4] = { 1,1,-1,-1 };
bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool canGo(int dir,int ndir) {
	if (dir <= 2) return dir == ndir || dir + 1 == ndir;
	else return ndir == 3;
}
void _init() {
	memset(MAP, 0, sizeof(MAP));
	memset(Visit, 0, sizeof(Visit));
	ans = -1;
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}
}
void DFS(int x, int y, int dir, int cnt) {
	
	if (x == stx && y == sty && cnt > 0) {
		ans = max(ans, cnt);
		return;
	}

	for (int ndir = dir; ndir <= dir + 1; ndir++) {
		
		
		int nx = x + dx[ndir];
		int ny = y + dy[ndir];
		int num = MAP[ny][nx];

		if (!isInside(nx, ny)) continue;
		if (!canGo(dir, ndir)) continue;
		if (ny < sty) continue;
		if (Visit[num]) continue;

		Visit[num] = true;
		DFS(nx, ny, ndir, cnt + 1);
		Visit[num] = false;
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		_init();
		_input();


		for (int i = 0; i <= N - 2; i++) {
			for (int j = 1; j <= N - 1; j++) {
			
				memset(Visit, 0, sizeof(Visit));
				stx = j;
				sty = i;
				DFS(stx, sty, 0, 0);
			}
		}

		cout << "#" << t << " " << ans << endl;
	}
	


}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}
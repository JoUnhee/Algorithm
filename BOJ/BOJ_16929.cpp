#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>

using namespace std;

int N, M;
int stx, sty;
bool flag;
char MAP[50][50];
map<char, int> check;
bool visit[50][50];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0,1,0,-1 };
bool canGo(int nDir, int dir,int cnt) {
	if (dir == 0) {
		if (cnt == 0) return nDir == 0;
		return nDir == 0 || nDir == 1;
	}
	else if (dir == 1) return nDir != 3;
	else if (dir == 2) return nDir != 0;
	else if (dir == 3) return nDir != 1;
}
bool isInside(int x, int y) {
	return x >= 0 && x < M && y >= 0 && y < N;
}
void input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			check[MAP[i][j]]++;
		}
	}


}
void DFS(int x, int y, int dir, int type, int cnt) {

	if (x == stx && y == sty && cnt != 0) {
		flag = true;
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (!canGo(i, dir, cnt)) continue;
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!isInside(nx, ny)) continue;
			if (visit[ny][nx]) continue;
			if (type != MAP[ny][nx]) continue;
			if (sty > ny) continue;

			visit[ny][nx] = true;
			DFS(nx, ny, i, type, cnt + 1);
			visit[ny][nx] = false;
			if (flag) return;
		}
	}
}
void solve() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (check[MAP[i][j]] < 4) continue;
			stx = j, sty = i;

			DFS(j, i, 0, MAP[i][j], 0);

			if (flag) {
				cout << "Yes" << endl;
				return;
			}
		}

	}

	if (!flag) {
		cout << "No" << endl;
	}

	return;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();
	
}
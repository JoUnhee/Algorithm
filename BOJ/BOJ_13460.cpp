#include <cstring>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define MAXN 10

using namespace std;
typedef struct Pos{
	int x;
	int y;
};

int N, M;
char B[MAXN][MAXN];
bool visit[MAXN][MAXN][MAXN][MAXN];
vector<Pos> st;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };

void _init() {
	memset(B, 0, sizeof(B));
	memset(visit, 0, sizeof(visit));
	st.resize(2);
	st[0].y = 0;
	st[0].x = 0;
	st[1].y = 0;
	st[1].x = 0;
}
void _input() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> B[i][j];

			if (B[i][j] == 'R') {
				B[i][j] = '.';
				st[0].x = j;
				st[0].y = i;
			}
			else if (B[i][j] == 'B') {
				B[i][j] = '.';
				st[1].x = j;
				st[1].y = i;
			}
		}
	}
}
void print(vector<Pos> cur) {
	char tmp[MAXN][MAXN];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp[i][j] = B[i][j];
		}
	}
	
	for (int i = 0; i < 2; i++) {
		int x = cur[i].x;
		int y = cur[i].y;

		tmp[y][x] = (i == 0 ? 'R' : 'B');
	}
	printf("-------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%2c", tmp[i][j]);
		}
		printf("\n");
	}
}
int check(int rx, int ry, int bx, int by, int dir) {
	if (dir == 0) {
		if (ry == by) {
			if (rx < bx) return 0;
			else return 1;
		}
		return 0;
	}
	else if (dir == 1) {
		if (rx == bx) {
			if (ry < by) return 0;
			else return 1;
		}
		return 0;
	}
	else if (dir == 2) {
		if (ry == by) {
			if (rx > bx) return 0;
			else return 1;
		}
		return 0;
	}
	else if (dir == 3) {
		if (rx == bx) {
			if (ry > by) return 0;
			else return 1;
		}
		return 0;
	}

}
int solution() {

	queue<vector<Pos>> q;
	q.push(st);
	visit[st[0].y][st[0].x][st[1].y][st[1].x] = 0;
	int ret = 0;
	while (!q.empty() && ret <= 10) {
		int sz = q.size();

		printf("===============%2d=============\n", ret);
		for (int s = 0; s < sz; s++) {
			vector<Pos> Curp(2);
			Curp[0] = q.front()[0];
			Curp[1] = q.front()[1];
			q.pop();


			if (B[Curp[0].y][Curp[0].x] == 'O') {
				if (B[Curp[1].y][Curp[1].x] == 'O') continue;
				else {
					return ret;
				}
			}

			for (int dir = 0; dir < 4; dir++) {
				vector<Pos> Npos(2);
				Npos[0].y = 0;
				Npos[0].x = 0;
				Npos[1].y = 0;
				Npos[1].x = 0;
				// 처음 움직일 돌 판단

				int idx = 0;

				idx = check(Curp[0].x, Curp[0].y, Curp[1].x, Curp[1].y, dir);

				for (int cnt = 0; cnt < 2; cnt++) {
					int x = Curp[idx].x;
					int y = Curp[idx].y;
					if (cnt == 0) {
						while (B[y + dy[dir]][x + dx[dir]] != '#' && B[y + dy[dir]][x + dx[dir]] != 'O' && !(Curp[1 - idx].y == y + dy[dir] && Curp[1 - idx].x == x + dx[dir])) {
							y += dy[dir];
							x += dx[dir];
						}
					}
					else {
						while (B[y + dy[dir]][x + dx[dir]] != '#' && B[y + dy[dir]][x + dx[dir]] != 'O' && !(Npos[1 - idx].y == y + dy[dir] && Npos[1 - idx].x == x + dx[dir])) {
							y += dy[dir];
							x += dx[dir];
						}
					}
					if (B[y + dy[dir]][x + dx[dir]] == 'O') {
						Npos[idx].x = x + dx[dir];
						Npos[idx].y = y + dy[dir];
					}
					else{
						Npos[idx].x = x;
						Npos[idx].y = y;
					}
					idx = 1 - idx;
				}

				int rx = Npos[0].x;
				int ry = Npos[0].y;
				int bx = Npos[1].x;
				int by = Npos[1].y;

				if (visit[ry][rx][by][bx] != false) continue;
				if (B[by][bx] == 'O') continue;
				visit[ry][rx][by][bx] = true;
				q.push(Npos);
				print(Npos);
			}

		}
		ret++;
	}
	return -1;
}
void solve() {
	
	_init();
	_input();

	int ans = solution();

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}

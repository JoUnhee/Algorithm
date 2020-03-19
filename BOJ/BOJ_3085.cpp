#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

int N;
int dx[2] = { 1,0 };
int dy[2] = { 0,1 };
char MAP[50][50];

bool isInside(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N;
}
void cpy(char tmap[][50]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tmap[i][j] = MAP[i][j];
		}
	}
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for(int j = 0 ; j < N; j++){
			cin >> MAP[i][j];
		}
	}
}
int check(char map[][50],int x,int y,int dir) {

	int tx = x;
	int ty = y;
	int cnt = 0;
	char obj = map[y][x];
	if (dir == 0) { // ¼¼·Î
		while (isInside(tx, ty) && map[ty][tx] == obj) {
			cnt++, ty--;
		}

		ty = y + 1;
		while (isInside(tx, ty) && map[ty][tx] == obj) {
			cnt++, ty++;
		}
	}
	else {
		while (isInside(tx, ty) && map[ty][tx] == obj) {
			cnt++, tx--;
		}
		tx = x + 1;
		while (isInside(tx, ty) && map[ty][tx] == obj) {
			cnt++, tx++;
		}
	}

	return cnt;
}
int solve() {
	
	_input();
	int ret = 0;

	for (int y = 0; y < N; y++) {
		for(int x = 0 ; x < N; x++){
			for (int i = 0; i < 2; i++) {
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (isInside(nx, ny)) {
					char tmap[50][50];
					cpy(tmap);

					char tmp = tmap[ny][nx];
					tmap[ny][nx] = tmap[y][x];
					tmap[y][x] = tmp;

					ret = max(ret, check(tmap, x, y, 0));
					ret = max(ret, check(tmap, x, y, 1));
					ret = max(ret, check(tmap, nx, ny, 0));
					ret = max(ret, check(tmap, nx, ny, 1));
				}
			}
		}
	}
	return ret;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	int ans = 0;

	ans = solve();

	cout << ans << endl;

}